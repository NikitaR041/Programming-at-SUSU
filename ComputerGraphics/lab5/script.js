// Interactive cubic Bezier with 4 control points, draggable, show mouse coords.

const canvas = document.getElementById('c');
const ctx = canvas.getContext('2d');
const coordsLabel = document.getElementById('coords');
const resetBtn = document.getElementById('resetBtn');
const stepsRange = document.getElementById('steps');

let rect = canvas.getBoundingClientRect();

function windowToCanvas(x, y) {
  rect = canvas.getBoundingClientRect();
  return { x: x - rect.left, y: y - rect.top };
}

// Initial control points (P0..P3)
let pts = [
  { x: 100, y: 500 }, // P0
  { x: 250, y: 100 }, // P1
  { x: 650, y: 100 }, // P2
  { x: 800, y: 500 }  // P3
];

const POINT_RADIUS = 7;
let dragIndex = -1; // index of point being dragged, -1 if none
let isMouseDown = false;

// Utility: cubic Bezier point at parameter t given points p0..p3
function cubicBezierPoint(p0, p1, p2, p3, t) {
  // Using Bernstein polynomials
  const u = 1 - t;
  const tt = t * t;
  const uu = u * u;
  const uuu = uu * u;
  const ttt = tt * t;

  const x = uuu * p0.x +
            3 * uu * t * p1.x +
            3 * u * tt * p2.x +
            ttt * p3.x;
  const y = uuu * p0.y +
            3 * uu * t * p1.y +
            3 * u * tt * p2.y +
            ttt * p3.y;
  return { x, y };
}

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Draw control polygon
  ctx.lineWidth = 1;
  ctx.strokeStyle = '#999';
  ctx.setLineDash([6,6]);
  ctx.beginPath();
  ctx.moveTo(pts[0].x, pts[0].y);
  for (let i=1;i<4;i++) ctx.lineTo(pts[i].x, pts[i].y);
  ctx.stroke();
  ctx.setLineDash([]);

  // Draw control points
  for (let i=0;i<4;i++){
    ctx.beginPath();
    ctx.fillStyle = (i === dragIndex) ? '#ff8c00' : '#0074D9';
    ctx.strokeStyle = '#222';
    ctx.lineWidth = 1;
    ctx.arc(pts[i].x, pts[i].y, POINT_RADIUS, 0, Math.PI*2);
    ctx.fill();
    ctx.stroke();

    // label Pi
    ctx.fillStyle = '#111';
    ctx.font = '12px Arial';
    ctx.fillText('P' + i, pts[i].x + POINT_RADIUS + 6, pts[i].y - POINT_RADIUS - 6);
  }

  // Draw the Bezier curve sampling many points
  ctx.lineWidth = 2;
  ctx.strokeStyle = '#d4006e';
  ctx.beginPath();

  const steps = Math.max(50, parseInt(stepsRange.value, 10)); // number of segments
  for (let i=0;i<=steps;i++){
    const t = i / steps;
    const p = cubicBezierPoint(pts[0], pts[1], pts[2], pts[3], t);
    if (i===0) ctx.moveTo(p.x, p.y);
    else ctx.lineTo(p.x, p.y);
  }
  ctx.stroke();

  // Optionally draw a thinner polyline of computed points (for debugging)
  // ctx.strokeStyle = 'rgba(0,0,0,0.1)';

  // Draw direction arrows every 0.1 t (optional)
  // for visual feedback skip for clarity

}

// find index of control point under mouse (within radius), or -1
function hitTest(mouseX, mouseY) {
  for (let i=0;i<pts.length;i++){
    const dx = mouseX - pts[i].x;
    const dy = mouseY - pts[i].y;
    if (dx*dx + dy*dy <= (POINT_RADIUS+4)*(POINT_RADIUS+4)) return i;
  }
  return -1;
}

// Mouse handlers
canvas.addEventListener('mousedown', (e) => {
  isMouseDown = true;
  const c = windowToCanvas(e.clientX, e.clientY);
  const idx = hitTest(c.x, c.y);
  if (idx !== -1) {
    dragIndex = idx;
  } else {
    dragIndex = -1;
  }
});

canvas.addEventListener('mousemove', (e) => {
  const c = windowToCanvas(e.clientX, e.clientY);
  coordsLabel.textContent = `Координаты: (x: ${Math.round(c.x)}, y: ${Math.round(c.y)})`;
  if (isMouseDown && dragIndex !== -1) {
    // Move point
    pts[dragIndex].x = c.x;
    pts[dragIndex].y = c.y;
    draw();
  } else {
    // highlight point under cursor
    const idx = hitTest(c.x, c.y);
    if (idx !== dragIndex) {
      // set dragIndex as highlight only when not dragging
      // use a temporary highlight by storing highlightIdx if needed
    }
  }
});

canvas.addEventListener('mouseup', (e) => {
  isMouseDown = false;
  dragIndex = -1;
});

canvas.addEventListener('mouseleave', (e) => {
  isMouseDown = false;
  dragIndex = -1;
  coordsLabel.textContent = `Координаты: (x: -, y: -)`;
});

// Touch support (mobile)
canvas.addEventListener('touchstart', (e) => {
  e.preventDefault();
  const touch = e.touches[0];
  const c = windowToCanvas(touch.clientX, touch.clientY);
  const idx = hitTest(c.x, c.y);
  if (idx !== -1) dragIndex = idx;
  isMouseDown = true;
});

canvas.addEventListener('touchmove', (e) => {
  e.preventDefault();
  if (!isMouseDown) return;
  const touch = e.touches[0];
  const c = windowToCanvas(touch.clientX, touch.clientY);
  coordsLabel.textContent = `Координаты: (x: ${Math.round(c.x)}, y: ${Math.round(c.y)})`;
  if (dragIndex !== -1) {
    pts[dragIndex].x = c.x;
    pts[dragIndex].y = c.y;
    draw();
  }
});

canvas.addEventListener('touchend', (e) => {
  isMouseDown = false;
  dragIndex = -1;
});

// Reset points button
resetBtn.addEventListener('click', () => {
  pts = [
    { x: 100, y: 500 },
    { x: 250, y: 100 },
    { x: 650, y: 100 },
    { x: 800, y: 500 }
  ];
  draw();
});

stepsRange.addEventListener('input', () => draw());

// initial draw
draw();
