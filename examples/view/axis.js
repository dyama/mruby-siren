
function make_line(src, dst, colorHex, dashed) {
  var geom = new THREE.Geometry(), mat;
  if(dashed) {
    mat = new THREE.LineDashedMaterial({linewidth: 1, color: colorHex, dashSize: 1, gapSize: 1});
  }
  else {
    mat = new THREE.LineBasicMaterial({linewidth: 1, color: colorHex});
  }
  geom.vertices.push(src.clone());
  geom.vertices.push(dst.clone());
  geom.computeLineDistances();
  return new THREE.Line(geom, mat, THREE.LineSegments);
}

// Axis
(function () {
  var length = 10;
  var axes = new THREE.Object3D();
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(length, 0, 0), 0xFF0000, false)); // +X
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(-length, 0, 0), 0xFF0000, true)); // -X
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, length, 0), 0x00FF00, false)); // +Y
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, -length, 0), 0x00FF00, true)); // -Y
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, 0, length), 0x0000FF, false)); // +Z
  axes.add(make_line(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, 0, -length), 0x0000FF, true)); // -Z
  scene.add(axes);
})();

// Grid
(function () {
  var grid = new THREE.Object3D();
  var size_h = 10;
  var size_w = 10;
  var span   = 10;

  var hlf_w = size_w / 2;
  var max_w = hlf_w * span;
  var min_w = hlf_w *-span;
  var hlf_h = size_h / 2;
  var max_h = hlf_h / 2 * span;
  var min_h = hlf_h / 2 *-span;

  var color = 0x5F5F5F;
  var color_strong = 0xA0A0A0;

  for (var i = 0; i <= size_w; i++) {
    grid.add(make_line(
          new THREE.Vector3(min_w, span * (i - hlf_w), 0),
          new THREE.Vector3(max_w, span * (i - hlf_w), 0),
          hlf_w == i ? color_strong : color, false));
  }

  for (var i = 0; i <= size_h; i++) {
    grid.add(make_line(
          new THREE.Vector3(span * (i - hlf_h), min_w, 0),
          new THREE.Vector3(span * (i - hlf_h), max_w, 0),
          hlf_h == i ? color_strong : color, false));
  }

  scene.add(grid);
})();
