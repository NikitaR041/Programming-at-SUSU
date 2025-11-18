const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

//Контроллеры
const startBtn = document.getElementById('startBtn');
const pauseBtn = document.getElementById('pauseBtn');
const resetBtn = document.getElementById('resetBtn');

const velRange = document.getElementById('velRange');
const velVal = document.getElementById('velVal');

const rotRange = document.getElementById('rotRange');
const rotVal = document.getElementById('rotVal');

const minScaleInp = document.getElementById('minScale');
const maxScaleInp = document.getElementById('maxScale');
const scaleSpeedRange = document.getElementById('scaleSpeed');
const scaleVal = document.getElementById('scaleVal');

let width = canvas.width;
let height = canvas.height;

//Свойства типа square
let square = {
  x: width / 2,  // центр x
  y: height / 2, // центр y
  size: 120,     // Базовая длина
  angle: 0,    // Текущий угол поворота
  //Угловая скорость (радианах/кадр)
  rotationSpeed: parseFloat(rotRange.value),
  //Скорость по х и у (pixels per frame)
  vx: parseFloat(velRange.value),  
  vy: parseFloat(velRange.value), 
  scale: 1.0,   // Корректный размер
  minScale: parseFloat(minScaleInp.value),
  maxScale: parseFloat(maxScaleInp.value),
  scaleSpeed: parseFloat(scaleSpeedRange.value),
  growing: true // Увеличение масшата в Real-time
};

let running = true;
let rafId = null;

// Метод, вычисляет координаты углов квадрата 
// (после масштабирования и поворота),
//  возвращает массив точек
function getSquareCorners(sq) {
  const half = (sq.size * sq.scale) / 2;
  //локальные углы относительно центра (CCW)
  const local = [
    { x: -half, y: -half },
    { x: half, y: -half },
    { x: half, y: half },
    { x: -half, y: half }
  ];
  const cosA = Math.cos(sq.angle);
  const sinA = Math.sin(sq.angle);
  return local.map(p => {
    return {
      x: sq.x + p.x * cosA - p.y * sinA,
      y: sq.y + p.x * sinA + p.y * cosA
    };
  });
}

function checkAndResolveCollisions(sq) {
  const corners = getSquareCorners(sq);
  let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
  for (const c of corners) {
    if (c.x < minX) minX = c.x;
    if (c.x > maxX) maxX = c.x;
    if (c.y < minY) minY = c.y;
    if (c.y > maxY) maxY = c.y;
  }

  if (minX <= 0 && sq.vx < 0) {
    sq.vx = -sq.vx;
    sq.x += Math.abs(0 - minX) + 1;
  } else if (maxX >= width && sq.vx > 0) {
    sq.vx = -sq.vx;
    sq.x -= Math.abs(maxX - width) + 1;
  }

  if (minY <= 0 && sq.vy < 0) {
    sq.vy = -sq.vy;
    sq.y += Math.abs(0 - minY) + 1;
  } else if (maxY >= height && sq.vy > 0) {
    sq.vy = -sq.vy;
    sq.y -= Math.abs(maxY - height) + 1;
  }
}

function drawAxes() {
  ctx.save();
  ctx.strokeStyle = 'rgba(0,0,0,0.06)';
  ctx.beginPath();
  ctx.moveTo(0, 0); ctx.lineTo(width, 0);
  ctx.moveTo(0, 0); ctx.lineTo(0, height);
  ctx.stroke();
  ctx.restore();
}

function drawSquare(sq) {
  ctx.save();
  ctx.translate(sq.x, sq.y);
  ctx.rotate(sq.angle);
  ctx.scale(sq.scale, sq.scale);

  ctx.fillStyle = '#2e86de';
  ctx.strokeStyle = '#1b4f72';
  ctx.lineWidth = 3 / Math.max(1, sq.scale); 
  ctx.fillRect(-sq.size / 2, -sq.size / 2, sq.size, sq.size);
  ctx.strokeRect(-sq.size / 2, -sq.size / 2, sq.size, sq.size);
  ctx.restore();
}

function step() {
  square.x += square.vx;
  square.y += square.vy;

  square.angle += square.rotationSpeed;

  if (square.growing) {
    square.scale += square.scaleSpeed;
    if (square.scale >= square.maxScale) {
      square.scale = square.maxScale;
      square.growing = false;
    }
  } else {
    square.scale -= square.scaleSpeed;
    if (square.scale <= square.minScale) {
      square.scale = square.minScale;
      square.growing = true;
    }
  }

  checkAndResolveCollisions(square);
}

function render() {
  ctx.clearRect(0, 0, width, height);
  drawSquare(square);
}

function loop() {
  if (!running) return;
  step();
  render();
  rafId = requestAnimationFrame(loop);
}

startBtn.addEventListener('click', () => {
  if (!running) {
    running = true;
    rafId = requestAnimationFrame(loop);
  }
});
pauseBtn.addEventListener('click', () => {
  running = false;
  if (rafId) cancelAnimationFrame(rafId);
});
resetBtn.addEventListener('click', () => {
  square.x = width / 2;
  square.y = height / 2;
  square.size = 120;
  square.angle = 0;
  square.scale = 1.0;
  square.vx = parseFloat(velRange.value);
  square.vy = parseFloat(velRange.value) * 0.7; 
  square.minScale = parseFloat(minScaleInp.value);
  square.maxScale = parseFloat(maxScaleInp.value);
  square.scaleSpeed = parseFloat(scaleSpeedRange.value);
  square.rotationSpeed = parseFloat(rotRange.value);
  square.growing = true;
});

velRange.addEventListener('input', () => {
  const v = parseFloat(velRange.value);
  velVal.textContent = v.toFixed(1);
  square.vx = (square.vx >= 0 ? 1 : -1) * v;
  square.vy = (square.vy >= 0 ? 1 : -1) * v * 0.7;
});

rotRange.addEventListener('input', () => {
  const r = parseFloat(rotRange.value);
  rotVal.textContent = r.toFixed(2);
  square.rotationSpeed = r;
});

scaleSpeedRange.addEventListener('input', () => {
  scaleVal.textContent = parseFloat(scaleSpeedRange.value).toFixed(3);
  square.scaleSpeed = parseFloat(scaleSpeedRange.value);
});

minScaleInp.addEventListener('change', () => {
  const v = parseFloat(minScaleInp.value);
  if (v >= 0.05 && v < square.maxScale) square.minScale = v;
});
maxScaleInp.addEventListener('change', () => {
  const v = parseFloat(maxScaleInp.value);
  if (v > square.minScale) square.maxScale = v;
});

window.addEventListener('resize', () => {
});

velVal.textContent = parseFloat(velRange.value).toFixed(1);
rotVal.textContent = parseFloat(rotRange.value).toFixed(2);
scaleVal.textContent = parseFloat(scaleSpeedRange.value).toFixed(3);

square.vx = parseFloat(velRange.value);
square.vy = parseFloat(velRange.value) * 0.7;

rafId = requestAnimationFrame(loop);
