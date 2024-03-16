#version 330 core

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 modelMat;

layout(std140) uniform CameraData {
    vec4 position;
    mat4 viewMat;
    mat4 projMat;
};

out VSOut {
    vec4 worldPos;
    vec3 worldNormal;
    vec3 viewPos;
}vsOut;

void main() {
    vsOut.worldPos = projMat * viewMat * modelMat * vec4(vPos, 1.0);
    vsOut.worldNormal = normalize(transpose(inverse(mat3(modelMat))) * vNormal);
    vsOut.viewPos = vec3(position);

    gl_Position = vsOut.worldPos;
}
