
// MODEL(Face)
for (var i = 0; i<fs.length; i++) {
  var material = new THREE.MeshPhongMaterial({color: modelcolor});
  material.side = THREE.DoubleSide;
  var model = new THREE.Mesh(fs[i], material);
  scene.add(model);
  models.push(model);

  // var edge = new THREE.EdgesHelper(model, "#3F3F3F");
  // edge.material.linewidth = 4;
  // scene.add(edge);
}

// MODEL(Edge)
for (var i = 0; i<es.length; i++) {
  var material = new THREE.LineBasicMaterial({linewidth: 4, color: 'red'});
  var model = new THREE.Line(es[i], material);
  scene.add(model);
  models.push(model);
}

