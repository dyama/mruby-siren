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

window.addEventListener("click", function(e) {
  if (!drag && e.button == 0) {
    var objs = get_objs(e);
    if (!shift) {
      control.detach();
    }
    if (objs.length > 0) {
      control.attach(objs[0].object);
    }
  }
}, false);

var shift = false;
var down = 0;
var button = 0;
var drag = false;
window.addEventListener('keydown', function(e) {
  down = e.keyCode;
  switch ( event.keyCode ) {
    case 81: // Q
      control.setSpace( control.space === "local" ? "world" : "local" );
      break;
    case 16: // shift
      shift = true;
      break;
    case 17: // Ctrl
      control.setTranslationSnap( 100 );
      control.setRotationSnap( THREE.Math.degToRad( 15 ) );
      break;
    case 87: // W
      control.setMode( "translate" );
      break;
    case 69: // E
      control.setMode( "rotate" );
      break;
    case 82: // R
      control.setMode( "scale" );
      break;
    case 187:
    case 107: // +, =, num+
      control.setSize( control.size + 0.1 );
      break;
    case 189:
    case 109: // -, _, num-
      control.setSize( Math.max( control.size - 0.1, 0.1 ) );
      break;
  }
}, false);

window.addEventListener('keyup',   function(e) {
  down = 0;
  switch ( event.keyCode ) {
    case 16: // shift
      shift = false;
      break;
    case 17: // Ctrl
      control.setTranslationSnap( null );
      control.setRotationSnap( null );
      break;
  }
}, false);

var prev;

window.addEventListener('mousedown', function(e) {
  prev = new THREE.Vector2(e.offsetX, e.offsetY);
  button = e.button;
}, false);

window.addEventListener('mouseup',   function(e) {
  button = -1;
  delete prev;
}, false);

window.addEventListener("mousemove", function(e) {
  if (button >= 0) {
    var curr = new THREE.Vector2(e.offsetX, e.offsetY);
    var dist = typeof(prev) != 'undefined' ? curr.distanceTo(prev) : 0;
    drag = dist > 2;
  }
  else {
    drag = false;
  }
}, false);

