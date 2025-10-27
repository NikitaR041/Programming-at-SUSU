const canvas = document.getElementById("canvas");
const ctx = canvas.getContext("2d");

const nSlider = document.getElementById("n");
const kSlider = document.getElementById("k");
const thicknessSlider = document.getElementById("thickness");
const colorPicker = document.getElementById("color");

const nVal = document.getElementById("nVal");
const kVal = document.getElementById("kVal");
const thicknessVal = document.getElementById("thicknessVal");

function plot(x, y, c, color) {
    ctx.fillStyle = `rgba(${color.r}, ${color.g}, ${color.b}, ${c})`;
    ctx.fillRect(x, y, 1, 1);
}

function hexToRgb(hex) {
    const bigint = parseInt(hex.slice(1), 16);
    return { 
        r: (bigint >> 16) & 255,
        g: (bigint >> 8) & 255,
        b: bigint & 255
    };
}

function fpart(x) { return x - Math.floor(x); }
function rfpart(x) { return 1 - fpart(x); }

// === Алгоритм Ву (с поддержкой толщины линии) ===
function drawWuLine(x0, y0, x1, y1, color, thickness=1) {
    const steep = Math.abs(y1 - y0) > Math.abs(x1 - x0);
    if (steep) [x0, y0] = [y0, x0], [x1, y1] = [y1, x1];
    if (x0 > x1) [x0, x1] = [x1, x0], [y0, y1] = [y1, y0];

    const dx = x1 - x0;
    const dy = y1 - y0;
    const gradient = dx === 0 ? 1 : dy / dx;

    let xEnd = Math.round(x0);
    let yEnd = y0 + gradient * (xEnd - x0);
    let xGap = rfpart(x0 + 0.5);
    let xPixel1 = xEnd;
    let yPixel1 = Math.floor(yEnd);

    if (steep) {
        plot(yPixel1, xPixel1, rfpart(yEnd) * xGap, color);
        plot(yPixel1 + 1, xPixel1, fpart(yEnd) * xGap, color);
    } else {
        plot(xPixel1, yPixel1, rfpart(yEnd) * xGap, color);
        plot(xPixel1, yPixel1 + 1, fpart(yEnd) * xGap, color);
    }

    let intery = yEnd + gradient;

    xEnd = Math.round(x1);
    yEnd = y1 + gradient * (xEnd - x1);
    xGap = fpart(x1 + 0.5);
    let xPixel2 = xEnd;
    let yPixel2 = Math.floor(yEnd);

    if (steep) {
        for (let x = xPixel1 + 1; x < xPixel2; x++) {
            for (let t = -Math.floor(thickness / 2); t <= Math.floor(thickness / 2); t++) {
                plot(Math.floor(intery) + t, x, rfpart(intery), color);
                plot(Math.floor(intery) + t + 1, x, fpart(intery), color);
            }
            intery += gradient;
        }
    } else {
        for (let x = xPixel1 + 1; x < xPixel2; x++) {
            for (let t = -Math.floor(thickness / 2); t <= Math.floor(thickness / 2); t++) {
                plot(x, Math.floor(intery) + t, rfpart(intery), color);
                plot(x, Math.floor(intery) + t + 1, fpart(intery), color);
            }
            intery += gradient;
        }
    }
}

// === Построение звезды {n/k} ===
function drawStar(n, k, color, thickness) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    const R = 250;
    const cx = canvas.width / 2;
    const cy = canvas.height / 2;

    const points = [];
    for (let i = 0; i < n; i++) {
        const angle = (2 * Math.PI * i) / n - Math.PI / 2;
        points.push({
            x: cx + R * Math.cos(angle),
            y: cy + R * Math.sin(angle)
        });
    }

    let visited = Array(n).fill(false);
    let i = 0;
    do {
        const start = i;
        do {
            const next = (i + k) % n;
            drawWuLine(points[i].x, points[i].y, points[next].x, points[next].y, color, thickness);
            i = next;
        } while (i !== start);
        visited[i] = true;
        i = visited.indexOf(false);
    } while (i !== -1);
}

// === Обновление значений ===
function update() {
    const n = parseInt(nSlider.value);
    const k = parseInt(kSlider.value);
    const thickness = parseFloat(thicknessSlider.value);
    const color = hexToRgb(colorPicker.value);

    nVal.textContent = n;
    kVal.textContent = k;
    thicknessVal.textContent = thickness;

    drawStar(n, k, color, thickness);
}

[nSlider, kSlider, thicknessSlider, colorPicker].forEach(slider => {
    slider.addEventListener("input", update);
});

update();
