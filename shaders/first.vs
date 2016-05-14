#version 120

// in
attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

uniform mat4 MVP;
uniform mat4 Normal;

// out
varying vec2 TexCoord;
varying vec3 normal0;

void main() {
    gl_Position = MVP * vec4(position.x, position.y, position.z, 1.0);

    TexCoord = texCoord;
    normal0 = (Normal * vec4(normal, 0.0)).xyz;
}
