#version 140

in vec3 vPosition;

uniform mat4 T;

void main() {
  gl_Position =  T*vec4(vPosition, 1.0);
}
