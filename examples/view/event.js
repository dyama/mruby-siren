var shift = false;

// Get objects by mouse position
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

// Key events

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

// Mouse events

var down = false;

window.addEventListener('mousedown', function(e) {
  down = true;
}, false);

window.addEventListener("mousemove", function(e) {
  drag = down;
}, false);

window.addEventListener('mouseup',   function(e) {
  var panel = document.getElementById("panel");
  if (e.clientX < panel.clientWidth && e.clientY < panel.clientHeight) {
    down = false;
    return;
  }
  if (!drag && down) {
    var objs = get_objs(e);
    if (!shift) {
      control.detach();
    }
    if (objs.length > 0) {
      control.attach(objs[0].object);
    }
  }
  down = false;
}, false);

// Button events

document.getElementById('plane').addEventListener('click', function(e) {
  var geom = new THREE.PlaneGeometry(10, 10, 1, 1);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[plane] Done.');
}, false);

document.getElementById('box').addEventListener('click', function(e) {
  var geom = new THREE.BoxGeometry(10, 10, 10);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[box] Done.');
}, false);

document.getElementById('cone').addEventListener('click', function(e) {
  var geom = new THREE.ConeGeometry(10, 30, 32);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[cone] Done.');
}, false);

document.getElementById('cylinder').addEventListener('click', function(e) {
  var geom = new THREE.CylinderGeometry(10, 10, 30, 32);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[cylinder] Done.');
}, false);

document.getElementById('sphere').addEventListener('click', function(e) {
  var geom = new THREE.SphereGeometry(10, 32, 32);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[sphere] Done.');
}, false);

document.getElementById('torus').addEventListener('click', function(e) {
  var geom = new THREE.TorusGeometry(20, 5, 16, 100);
  var mesh = new THREE.Mesh(geom, material_face);
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[torus] Done.');
}, false);

document.getElementById('duplicate').addEventListener('click', function(e) {
  if (typeof(control.object) == 'undefined') {
    log('[duplicate] No selected object.', true);
    return;
  }
  var mesh = control.object.clone();
  scene.add(mesh);
  models.push(mesh);
  control.detach();
  control.attach(mesh);
  log('[duplicate] Done.');
}, true);

document.getElementById('remove').addEventListener('click', function(e) {
  if (typeof(control.object) == 'undefined') {
    log('[remove] No selected object.', true);
    return;
  }
  var mesh = control.object;
  scene.remove(mesh);
  models = models.filter(function (e, i, a) {
    return e != mesh;
  });
  control.detach();
  mesh.geometry.dispose();
  log('[remove] Done.');
}, true);

document.getElementById('boundbox').addEventListener('click', function(e) {
  if (typeof(control.object) == 'undefined') {
    log('[boundbox] No selected object.', true);
    return;
  }
  var geom = control.object.geometry;
  geom.computeBoundingBox();
  var bnd = geom.boundingBox;
  log('[boundbox] min:' + bnd.min.x + ',' + bnd.min.y + ',' + bnd.min.z);
  log('[boundbox] max:' + bnd.max.x + ',' + bnd.max.y + ',' + bnd.max.z);
  log('[boundsphere] R:' + geom.boundingSphere.radius);
}, true);

function log(msg, is_alert) {
  if (is_alert) {
    msg = '<span class="alert">' + msg + '</span>';
  }
  var console = document.getElementById('log');
  console.innerHTML = console.innerHTML + '<br />\n' + msg;
  console.scrollTop = console.scrollHeight;
}

