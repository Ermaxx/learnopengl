#version 120

// in
attribute vec3 position;
attribute vec2 texCoord;

uniform mat4 MVP;

// out
varying vec2 TexCoord;

void main() {
     gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);
     TexCoord = texCoord;
}
