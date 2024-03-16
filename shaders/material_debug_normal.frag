#version 330 core

layout (location = 0) out vec4 FragColor;

in VSOut {
    vec4 worldPos;
    vec3 worldNormal;
    vec3 viewPos;
}vsIn;

void main() {
    vec3 norm = normalize(vsIn.worldNormal) * 0.5 + vec3(0.5);
    FragColor = vec4(norm, 1.0);
}
