// Affine animation: movement + rotation + scaling of a square with bouncing at canvas edges.
// Save as script.js and open index.html

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

// Controls
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

// Square state
let square = {
  x: width / 2,     // center x
  y: height / 2,    // center y
  size: 120,        // base side length
  angle: 0,         // current rotation angle (radians)
  rotationSpeed: parseFloat(rotRange.value), // angular speed (rad/frame)
  vx: parseFloat(velRange.value),  // speed x (pixels per frame)
  vy: parseFloat(velRange.value),  // speed y
  scale: 1.0,       // current scale
  minScale: parseFloat(minScaleInp.value),
  maxScale: parseFloat(maxScaleInp.value),
  scaleSpeed: parseFloat(scaleSpeedRange.value),
  growing: true     // whether currently increasing scale
};

let running = true;
let rafId = null;

// Utility: compute coordinates of square corners (after scale & rotation), returns array of points
function getSquareCorners(sq) {
  const half = (sq.size * sq.scale) / 2;
  // local corners relative to center (CCW)
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

// Check collision: find axis-aligned bbox from rotated corners and compare to canvas bounds
function checkAndResolveCollisions(sq) {
  const corners = getSquareCorners(sq);
  let minX = Infinity, minY = Infinity, maxX = -Infinity, maxY = -Infinity;
  for (const c of corners) {
    if (c.x < minX) minX = c.x;
    if (c.x > maxX) maxX = c.x;
    if (c.y < minY) minY = c.y;
    if (c.y > maxY) maxY = c.y;
  }

  // if outside on left or right -> reverse vx
  if (minX <= 0 && sq.vx < 0) {
    sq.vx = -sq.vx;
    // push inside
    sq.x += Math.abs(0 - minX) + 1;
  } else if (maxX >= width && sq.vx > 0) {
    sq.vx = -sq.vx;
    sq.x -= Math.abs(maxX - width) + 1;
  }

  // if outside on top or bottom -> reverse vy
  if (minY <= 0 && sq.vy < 0) {
    sq.vy = -sq.vy;
    sq.y += Math.abs(0 - minY) + 1;
  } else if (maxY >= height && sq.vy > 0) {
    sq.vy = -sq.vy;
    sq.y -= Math.abs(maxY - height) + 1;
  }
}

// Draw helper: axes for debugging optionally
function drawAxes() {
  ctx.save();
  ctx.strokeStyle = 'rgba(0,0,0,0.06)';
  ctx.beginPath();
  ctx.moveTo(0, 0); ctx.lineTo(width, 0);
  ctx.moveTo(0, 0); ctx.lineTo(0, height);
  ctx.stroke();
  ctx.restore();
}

// Draw square with current affine transforms (translate->rotate->scale->draw centered rect)
function drawSquare(sq) {
  ctx.save();
  ctx.translate(sq.x, sq.y);
  ctx.rotate(sq.angle);
  ctx.scale(sq.scale, sq.scale);

  ctx.fillStyle = '#2e86de';
  ctx.strokeStyle = '#1b4f72';
  ctx.lineWidth = 3 / Math.max(1, sq.scale); // keep stroke visible when scaled
  ctx.fillRect(-sq.size / 2, -sq.size / 2, sq.size, sq.size);
  ctx.strokeRect(-sq.size / 2, -sq.size / 2, sq.size, sq.size);
  ctx.restore();
}

// Main animation step
function step() {
  // Update physics / transforms
  // Move
  square.x += square.vx;
  square.y += square.vy;

  // Rotate (clockwise -> increase angle)
  square.angle += square.rotationSpeed;

  // Scale oscillation
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

  // Collision with boundaries (based on rotated bbox)
  checkAndResolveCollisions(square);
}

// Render frame
function render() {
  ctx.clearRect(0, 0, width, height);

  // optional grid / axes
  // drawAxes();

  // draw square
  drawSquare(square);

  // debug outline of bbox (for clarity)
  /* const corners = getSquareCorners(square);
  ctx.beginPath();
  ctx.strokeStyle = 'rgba(0,0,0,0.15)';
  ctx.moveTo(corners[0].x, corners[0].y);
  corners.slice(1).forEach(c => ctx.lineTo(c.x, c.y));
  ctx.closePath();
  ctx.stroke(); */
}

function loop() {
  if (!running) return;
  step();
  render();
  rafId = requestAnimationFrame(loop);
}

// Controls behavior
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
  // reset to center with default params
  square.x = width / 2;
  square.y = height / 2;
  square.size = 120;
  square.angle = 0;
  square.scale = 1.0;
  square.vx = parseFloat(velRange.value);
  square.vy = parseFloat(velRange.value) * 0.7; // slightly different vy
  square.minScale = parseFloat(minScaleInp.value);
  square.maxScale = parseFloat(maxScaleInp.value);
  square.scaleSpeed = parseFloat(scaleSpeedRange.value);
  square.rotationSpeed = parseFloat(rotRange.value);
  square.growing = true;
});

// Ranges & display updates
velRange.addEventListener('input', () => {
  const v = parseFloat(velRange.value);
  velVal.textContent = v.toFixed(1);
  // Update both components proportionally, keep sign
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

// resize handling (keeps canvas size constants; update width/height vars if needed)
window.addEventListener('resize', () => {
  // Optionally adapt canvas to new window
  // For now keep fixed size; if adapting, update width/height
});

// initialize velocities display
velVal.textContent = parseFloat(velRange.value).toFixed(1);
rotVal.textContent = parseFloat(rotRange.value).toFixed(2);
scaleVal.textContent = parseFloat(scaleSpeedRange.value).toFixed(3);

// initial velocities
square.vx = parseFloat(velRange.value);
square.vy = parseFloat(velRange.value) * 0.7;

// start animation
rafId = requestAnimationFrame(loop);
