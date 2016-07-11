
// MODEL(Face)
for (var i = 0; i<fs.length; i++) {
  var model = new THREE.Mesh(fs[i], material_face);
  scene.add(model);
  models.push(model);
}

// MODEL(Edge)
for (var i = 0; i<es.length; i++) {
  var material = new THREE.LineBasicMaterial({linewidth: 4, color: 'red'});
  var model = new THREE.Line(es[i], material_edge);
  scene.add(model);
  models.push(model);
}

