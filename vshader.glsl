#version 140

in vec3 vPosition;

uniform mat4 T;
uniform mat4 V;
uniform mat4 P;

void main() {
  gl_Position =  P*V*T*vec4(vPosition, 1.0);
}
