var w = window.innerWidth;
var h = window.innerHeight;
var aspect = w/h;

var models = [];
var modelcolor = 'slategray';
var selectedcolor = 'red';
var highlightcolor = 'royalblue';

var scene = new THREE.Scene();
scene.fog = new THREE.Fog(0xffffff, 0, 20750);

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

// EVENT
window.addEventListener('resize', function() {
  w = window.innerWidth;
  h = window.innerHeight;
  renderer.setSize(w, h);
  camera.aspect = aspect = w / h;
  camera.updateProjectionMatrix();
}, false);

function get_objs(e) {
  var rect = e.target.getBoundingClientRect();
  var mouseX = e.clientX - rect.left;
  var mouseY = e.clientY - rect.top;
  mouseX = (mouseX / w) * 2 - 1;
  mouseY = -(mouseY / h) * 2 + 1;
  var pos = new THREE.Vector3(mouseX, mouseY, 1);
  pos.unproject(camera);
  var ray = new THREE.Raycaster(camera.position, pos.sub(camera.position).normalize());
  return ray.intersectObjects(models);
}

window.addEventListener("mousemove", function(e) {
  var objs = get_objs(e);
  update_color_all();
  if (objs.length > 0) {
    var model = objs[0].object;
    if (!model.selected) {
      model.material.color.set(highlightcolor);
    }
  }
}, false);

function update_color_all()
{
  for (var i = 0; i<models.length; i++) {
    if (models[i].selected) {
      models[i].material.color.set(selectedcolor);
    }
    else {
      models[i].material.color.set(modelcolor);
    }
  }
}

function unselect_all()
{
  for (var i = 0; i<models.length; i++) {
    models[i].selected = false;  
  }
}

window.addEventListener("click", function(e) {
  if (e.button == 0) {
    var objs = get_objs(e);
    if (objs.length == 0) {
      unselect_all();
    }
    else {
      objs[0].object.selected = true;
    }
    update_color_all();
  }
}, false);

// CAMERA
var camera = new THREE.PerspectiveCamera(65, aspect, 1, 500000);
camera.position.set(-15, -25, 20);
camera.lookAt(new THREE.Vector3(40, 0, 0));
camera.up.set(0, 0, 1);

// RENDERER
var renderer = new THREE.WebGLRenderer({alpha: false});
renderer.setSize(w, h);
renderer.setClearColor(0x333333);
renderer.setFaceCulling(false);
//renderer.setFaceCulling(THREE.CullFaceFrontBack);
//renderer.setFaceCulling(THREE.CullFaceFront);
//renderer.setFaceCulling(THREE.CullFaceBack);
document.body.appendChild(renderer.domElement);

function render() {
  requestAnimationFrame(render);
  renderer.render(scene, camera);
}
render();

var controls = new THREE.OrbitControls(camera, renderer.domElement);
