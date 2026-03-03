// RGB -> HEX
function rgbToHex(r, g, b) {
  return "#" + [r, g, b].map(x =>
    x.toString(16).padStart(2, "0")
  ).join("").toUpperCase();
}

// RGB -> CMYK
function rgbToCmyk(r, g, b) {
  let c = 1 - (r / 255);
  let m = 1 - (g / 255);
  let y = 1 - (b / 255);
  let k = Math.min(c, m, y);
  c = ((c - k) / (1 - k)) || 0;
  m = ((m - k) / (1 - k)) || 0;
  y = ((y - k) / (1 - k)) || 0;
  return [c * 100, m * 100, y * 100, k * 100];
}

// CMYK -> RGB
function cmykToRgb(c, m, y, k) {
  let r = 255 * (1 - c/100) * (1 - k/100);
  let g = 255 * (1 - m/100) * (1 - k/100);
  let b = 255 * (1 - y/100) * (1 - k/100);
  return [Math.round(r), Math.round(g), Math.round(b)];
}

// RGB -> HSI
function rgbToHsi(r, g, b) {
  r /= 255; g /= 255; b /= 255;
  let intensity = (r + g + b) / 3;
  let minVal = Math.min(r, g, b);
  let saturation = 1 - (minVal / intensity || 0);
  let hue = Math.acos(
    (0.5 * ((r - g) + (r - b))) /
    Math.sqrt((r - g) * (r - g) + (r - b) * (g - b))
  ) * (180 / Math.PI);
  if (b > g) hue = 360 - hue;
  return [Math.round(hue), Math.round(saturation * 100), 
    Math.round(intensity * 100)];
}

// HSI -> RGB
function hsiToRgb(h, s, i) {
  s /= 100; i /= 100;
  let r, g, b;
  let rad = (Math.PI / 180) * h;

  if (h < 120) {
    b = i * (1 - s);
    r = i * (1 + (s * Math.cos(rad)) / Math.cos(Math.PI/3 - rad));
    g = 3 * i - (r + b);
  } else if (h < 240) {
    h = h - 120; rad = (Math.PI / 180) * h;
    r = i * (1 - s);
    g = i * (1 + (s * Math.cos(rad)) / Math.cos(Math.PI/3 - rad));
    b = 3 * i - (r + g);
  } else {
    h = h - 240; rad = (Math.PI / 180) * h;
    g = i * (1 - s);
    b = i * (1 + (s * Math.cos(rad)) / Math.cos(Math.PI/3 - rad));
    r = 3 * i - (g + b);
  }

  return [Math.max(0, Math.min(255, Math.round(r*255))),
          Math.max(0, Math.min(255, Math.round(g*255))),
          Math.max(0, Math.min(255, Math.round(b*255)))];
}

// -----------------------------
// Логика обновления
// -----------------------------

function updateFromRGB() {
  let r = +document.getElementById("r").value;
  let g = +document.getElementById("g").value;
  let b = +document.getElementById("b").value;

  let hex = rgbToHex(r, g, b);
  document.getElementById("rgb-preview").style.background = hex;
  document.getElementById("rgb-hex").textContent = hex;
}

function updateFromCMYK() {
  let c = +document.getElementById("c").value;
  let m = +document.getElementById("m").value;
  let y = +document.getElementById("y").value;
  let k = +document.getElementById("k").value;

  let [r, g, b] = cmykToRgb(c, m, y, k);
  let hex = rgbToHex(r, g, b);
  document.getElementById("cmyk-preview").style.background = hex;
  document.getElementById("cmyk-hex").textContent = hex;
}

function updateFromHSI() {
  let h = +document.getElementById("hue").value;
  let s = +document.getElementById("sat").value;
  let i = +document.getElementById("int").value;

  let [r, g, b] = hsiToRgb(h, s, i);
  let hex = rgbToHex(r, g, b);
  document.getElementById("hsi-preview").style.background = hex;
  document.getElementById("hsi-hex").textContent = hex;
}

// -----------------------------
// Подключаем события
// -----------------------------
document.querySelectorAll("#rgb-block input").forEach(inp => 
    inp.addEventListener("input", updateFromRGB));
document.querySelectorAll("#cmyk-block input").forEach(inp => 
    inp.addEventListener("input", updateFromCMYK));
document.querySelectorAll("#hsi-block input").forEach(inp => 
    inp.addEventListener("input", updateFromHSI));

// Стартовые значения
updateFromRGB();
updateFromCMYK();
updateFromHSI();
