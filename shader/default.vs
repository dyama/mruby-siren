attribute vec4 position;
attribute vec4 color;
uniform mat4 mvpMatrix;
varying vec4 vColor

void main(void) {
  vColor = color;
  gl_Position = mvpMatrix * position;
}

