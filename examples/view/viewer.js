// var view = document.getElementById("view");
// var w = view.clientWidth;
// var h = view.clientHeight;
var w = window.innerWidth;
var h = window.innerHeight;
var aspect = w / h;

var models = [];

var scene = new THREE.Scene();

// LIGHT
var dlight = new THREE.DirectionalLight('white');
dlight.position.set(2, 7, 10);
scene.add(dlight);

var supportLight = new THREE.DirectionalLight('white');
supportLight.position.set(-0.5, -8, -1);
scene.add(supportLight);

// EVENT
window.addEventListener('resize', function() {
  w = window.innerWidth;
  h = window.innerHeight;
  // w = view.clientWidth;
  // h = view.clientHeight;
  renderer.setSize(w, h);
  camera.aspect = aspect = w / h;
  camera.updateProjectionMatrix();
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
document.body.appendChild(renderer.domElement);
// view.appendChild(renderer.domElement);

var fps = 30;
var now;
var then = Date.now();
var interval = 1000/fps;
var delta;

function render() {
  requestAnimationFrame(render);
  now = Date.now();
  delta = now - then;
  if (delta > interval) {
    then = now - (delta % interval);
    control.update();
    renderer.render(scene, camera);
  }
}

// OrbitControls
var controls = new THREE.OrbitControls(camera, renderer.domElement);

// TransformControls
var control = new THREE.TransformControls( camera, renderer.domElement );
control.addEventListener( 'change', render );
scene.add(control);

render();

