#version 410
// Output for on-screen color
out vec4 outColor;

uniform vec3 color;

void main() {
    outColor = vec4(color, 1.0);
}