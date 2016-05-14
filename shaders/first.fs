#version 120

// in
varying vec2 TexCoord;
varying vec3 normal0;

uniform sampler2D ourTexture;
uniform vec3 lightDirection;

void main() {
    gl_FragColor = texture2D(ourTexture, TexCoord) * clamp(dot(-lightDirection, normal0), 0.04, 1.0);
}
