(() => {
  const canvas = document.getElementById('glCanvas');
  const ctx = canvas.getContext('2d');
  const loadSampleBtn = document.getElementById('loadSample');
  const resetBtn = document.getElementById('resetBtn');

  const tx = document.getElementById('tx'), ty = document.getElementById('ty'), 
    tz = document.getElementById('tz');
  const rx = document.getElementById('rx'), ry = document.getElementById('ry'), 
    rz = document.getElementById('rz');
  const s = document.getElementById('s'), sx = document.getElementById('sx'), 
    sy = document.getElementById('sy'), sz = document.getElementById('sz');
  const fov = document.getElementById('fov');
  const showEdges = document.getElementById('showEdges'), 
      showFaces = document.getElementById('showFaces');

  const setters = [
    ['tx', tx, 'txVal'], ['ty', ty, 'tyVal'], ['tz', tz, 'tzVal'],
    ['rx', rx, 'rxVal'], ['ry', ry, 'ryVal'], ['rz', rz, 'rzVal'],
    ['s', s, 'sVal'], ['sx', sx, 'sxVal'], ['sy', sy, 'syVal'],
         ['sz', sz, 'szVal'],
    ['fov', fov, 'fovVal']
  ];
  setters.forEach(([id, el, out]) => {
    const o = document.getElementById(out);
    if (!o) return;
    const update = () => { o.textContent = (el.type === 'range' && 
      (el.step && +el.step < 1)) ? 
            parseFloat(el.value).toFixed(2) : el.value; };
    el.addEventListener('input', update);
    update();
  });

  const vCountEl = document.getElementById('vCount'), 
      fCountEl = document.getElementById('fCount'), 
        centroidEl = document.getElementById('centroid');

  let model = { vertices: [], faces: [] };
  let originalVertices = [];
  let centroid = [0,0,0];

  const canvasW = canvas.width, canvasH = canvas.height;
  const cx = canvasW / 2, cy = canvasH / 2;

  function cloneVertices(vs) { return vs.map(v => [v[0], v[1], v[2]]); }

  function computeCentroid(vs) {
    if (!vs.length) return [0,0,0];
    const s = [0,0,0];
    vs.forEach(v => { s[0]+=v[0]; s[1]+=v[1]; s[2]+=v[2]; });
    return [s[0]/vs.length, s[1]/vs.length, s[2]/vs.length];
  }

  function degToRad(d){ return d * Math.PI / 180; }

  function rotateX(p, a){
    const ca = Math.cos(a), sa = Math.sin(a);
    return [p[0], p[1]*ca - p[2]*sa, p[1]*sa + p[2]*ca];
  }
  function rotateY(p, a){
    const ca = Math.cos(a), sa = Math.sin(a);
    return [p[0]*ca + p[2]*sa, p[1], -p[0]*sa + p[2]*ca];
  }
  function rotateZ(p, a){
    const ca = Math.cos(a), sa = Math.sin(a);
    return [p[0]*ca - p[1]*sa, p[0]*sa + p[1]*ca, p[2]];
  }

  function applyTransform(pOrig) {
    let p = [pOrig[0] - centroid[0], pOrig[1] - centroid[1],
         pOrig[2] - centroid[2]];

    // scale: uniform * per-axis
    const uniform = parseFloat(s.value);
    const sxv = parseFloat(sx.value) * uniform;
    const syv = parseFloat(sy.value) * uniform;
    const szv = parseFloat(sz.value) * uniform;
    p = [p[0] * sxv, p[1] * syv, p[2] * szv];
    const ax = degToRad(parseFloat(rx.value));
    const ay = degToRad(parseFloat(ry.value));
    const az = degToRad(parseFloat(rz.value));
    p = rotateX(p, ax);
    p = rotateY(p, ay);
    p = rotateZ(p, az);
    const txv = parseFloat(tx.value), tyv = parseFloat(ty.value),
       tzv = parseFloat(tz.value);
    return [p[0] + centroid[0] + txv, p[1] + centroid[1] + tyv,
       p[2] + centroid[2] + tzv];
  }
  function project(p) {
    const distance = parseFloat(fov.value);
    const z = p[2] + distance;
    const px = (p[0] * distance) / z;
    const py = (p[1] * distance) / z;
    return [cx + px, cy - py, z];
  }
  const lightDir = normalize([1, 1, 0.5]);
  function normalize(v){
    const L = Math.hypot(...v) || 1;
    return v.map(x => x / L);
  }
  function faceNormal(vA, vB, vC){
    const U = [vB[0]-vA[0], vB[1]-vA[1], vB[2]-vA[2]];
    const V = [vC[0]-vA[0], vC[1]-vA[1], vC[2]-vA[2]];
    const N = [
      U[1]*V[2] - U[2]*V[1],
      U[2]*V[0] - U[0]*V[2],
      U[0]*V[1] - U[1]*V[0]
    ];
    const L = Math.hypot(N[0], N[1], N[2]) || 1;
    return [N[0]/L, N[1]/L, N[2]/L];
  }
  function render() {
    ctx.clearRect(0,0,canvasW,canvasH);
    if (!model.vertices.length) return;
    const tVerts = model.vertices.map(v => applyTransform(v));
    const facesDraw = model.faces.map((face, idx) => {
      const verts = face.map(i => tVerts[i]);
      const avgZ = verts.reduce((s, v) => s + v[2], 0) / verts.length;
      let normal = [0,0,1];
      if (verts.length >= 3) normal = faceNormal(verts[0], verts[1], verts[2]);
      return { idx, verts, avgZ, normal, visible: true };
    });

    facesDraw.sort((a,b) => b.avgZ - a.avgZ);

    for (const f of facesDraw) {
      const proj = f.verts.map(v => project(v));
      const dot = f.normal[0]*lightDir[0] + f.normal[1]*lightDir[1] +
           f.normal[2]*lightDir[2];
      const shade = Math.max(0.08, dot);

      if (showFaces.checked) {
        ctx.beginPath();
        ctx.moveTo(proj[0][0], proj[0][1]);
        for (let i = 1; i < proj.length; i++) ctx.lineTo(proj[i][0], proj[i][1]);
        ctx.closePath();
        const base = 140;
        const colorVal = Math.round(base + shade * 100);
        ctx.fillStyle = `rgb(${colorVal}, ${colorVal}, ${255})`;
        ctx.fill();
      }

      if (showEdges.checked) {
        ctx.beginPath();
        ctx.moveTo(proj[0][0], proj[0][1]);
        for (let i = 1; i < proj.length; i++) ctx.lineTo(proj[i][0], proj[i][1]);
        ctx.closePath();
        ctx.strokeStyle = 'rgba(20,30,60,0.9)';
        ctx.lineWidth = 1;
        ctx.stroke();
      }
    }
  }

  function loadModelFromJSONText(txt) {
    try {
      const obj = JSON.parse(txt);
      if (!Array.isArray(obj.vertices) || !Array.isArray(obj.faces)) 
        throw new Error('Неверный формат: vertices/faces должны быть массивами');
      model.vertices = obj.vertices.map(v => [Number(v[0]),
           Number(v[1]), Number(v[2])]);
      model.faces = obj.faces.map(f => f.map(i => parseInt(i)));
      originalVertices = cloneVertices(model.vertices);
      centroid = computeCentroid(originalVertices);
      updateInfo();
      render();
    } catch (e) {
      alert('Ошибка при разборе файла: ' + e.message);
    }
  }

  loadSampleBtn.addEventListener('click', () => {
    const sample = {
      "vertices": [
        [-1,-1,-1],[1,-1,-1],[1,1,-1],[-1,1,-1],
        [-1,-1,1],[1,-1,1],[1,1,1],[-1,1,1]
      ],
      "faces": [
        [0,1,2,3],[4,5,6,7],[0,1,5,4],
        [2,3,7,6],[0,3,7,4],[1,2,6,5]
      ]
    };
    const scaled = JSON.stringify({
      vertices: sample.vertices.map(v => [v[0]*120, v[1]*120, v[2]*120]),
      faces: sample.faces
    }, null, 2);
    loadModelFromJSONText(scaled);
  });

  resetBtn.addEventListener('click', () => {
    tx.value = 0; ty.value = 0; tz.value = 0;
    rx.value = 0; ry.value = 0; rz.value = 0;
    s.value = 1; sx.value = 1; sy.value = 1; sz.value = 1;
    fov.value = 600;
    setters.forEach(([id, el, out]) => { const o = document.getElementById(out); 
            if (o) o.textContent = el.value; });
    if (originalVertices.length) {
      model.vertices = cloneVertices(originalVertices);
      centroid = computeCentroid(originalVertices);
      updateInfo();
      render();
    }
  });

  function updateInfo() {
    vCountEl.textContent = model.vertices.length;
    fCountEl.textContent = model.faces.length;
    centroidEl.textContent = centroid.map(v => v.toFixed(2)).join(', ');
  }

  render();

  const controlInputs = Array.from(document.querySelectorAll('.controls input'));
  controlInputs.forEach(inp => inp.addEventListener('input', render));
})();
