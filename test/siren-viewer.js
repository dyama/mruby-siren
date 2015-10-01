var w = window.innerWidth;
var h = window.innerHeight;
var aspect = w/h;

var modelcolor = 'slategray';

var scene = new THREE.Scene();
scene.fog = new THREE.Fog(0xffffff, 0, 750);

// var helper = new THREE.GridHelper(150, 50);
// helper.color1.setHex(0xffffff);
// helper.color2.setHex(0x7f7fff);
// scene.add(helper);

// LIGHT
var dlight = new THREE.DirectionalLight('white');
dlight.position.set(2, 7, 10);
scene.add(dlight);

var supportLight = new THREE.DirectionalLight('white');
supportLight.position.set(-0.5, -8, -1);
scene.add(supportLight);

// AXIS
function buildAxis(src, dst, colorHex, dashed) {
  var geom = new THREE.Geometry(), mat;
  if(dashed) {
    mat = new THREE.LineDashedMaterial({linewidth: 3, color: colorHex, dashSize: 1, gapSize: 1});
  }
  else {
    mat = new THREE.LineBasicMaterial({linewidth: 3, color: colorHex});
  }
  geom.vertices.push(src.clone());
  geom.vertices.push(dst.clone());
  geom.computeLineDistances();
  return new THREE.Line(geom, mat, THREE.LineSegments);
}
var length = 10;
var axes = new THREE.Object3D();
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(length, 0, 0), 0xFF0000, false)); // +X
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(-length, 0, 0), 0xFF0000, true)); // -X
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, length, 0), 0x00FF00, false)); // +Y
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, -length, 0), 0x00FF00, true)); // -Y
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, 0, length), 0x0000FF, false)); // +Z
axes.add(buildAxis(new THREE.Vector3(0, 0, 0), new THREE.Vector3(0, 0, -length), 0x0000FF, true)); // -Z
scene.add(axes);

// MODEL(Mesh)
var material = new THREE.MeshPhongMaterial({color: modelcolor});
model = new THREE.Mesh(g, material);
//model.position.set(-50, 0, 0);
scene.add(model);

// MODEL(Edge)
var edge = new THREE.EdgesHelper(model, "#3F3F3F");
edge.material.linewidth = 4;
scene.add(edge);

// EVENT
window.addEventListener('resize', function() {
  w = window.innerWidth
  h = window.innerHeight
  renderer.setSize(w, h);
  camera.aspect = aspect = w / h;
  camera.updateProjectionMatrix();
}, false);

window.addEventListener("mousemove", function(e) {
  var rect = e.target.getBoundingClientRect();
  var mouseX = e.clientX - rect.left;
  var mouseY = e.clientY - rect.top;
  mouseX = (mouseX / w) * 2 - 1;
  mouseY = -(mouseY / h) * 2 + 1;
  var pos = new THREE.Vector3(mouseX, mouseY, 1);
  pos.unproject(camera);
  var ray = new THREE.Raycaster(camera.position, pos.sub(camera.position).normalize());
  var obj = ray.intersectObjects([model]);
  material.color.set(modelcolor);
  if (obj.length > 0) {
    material.color.set('royalblue');
  }
}, false);

// CAMERA
var camera;
if (1) {
  camera = new THREE.PerspectiveCamera(65, aspect, 1, 1000);
  camera.position.set(-15, -25, 20);
  camera.lookAt(new THREE.Vector3(40, 0, 0));
  camera.up.set(0, 0, 1);
}
else {
  var d = 100;
  camera = new THREE.OrthographicCamera(-d * aspect, d * aspect, d, -d, 1, 1000);
  camera.position.set(-15, -20, 20);
  camera.lookAt(scene.position);
}

// RENDERER
var renderer = new THREE.WebGLRenderer({alpha: true});
renderer.setSize(w, h);
renderer.setClearColor(0x000000, 0);
document.body.appendChild(renderer.domElement);

function render() {
  requestAnimationFrame(render);
  // model.rotation.x += 0.01;
  // model.rotation.y += 0.01;
  // model.translateX(0.01);
  renderer.render(scene, camera);
}
render();

var controls = new THREE.OrbitControls(camera);
