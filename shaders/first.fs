#version 120

// in
varying vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
     gl_FragColor = texture2D(ourTexture, TexCoord);
}
