#version 330 core

float PI = 3.14159265359;

layout (location = 0) out vec4 FragColor;

//layout(std140) uniform MaterialData {
//    vec3 baseColor;
//    float metallic;
//    float roughness;
//};

uniform vec3 baseColor;
uniform float metallic;
uniform float roughness;

in VSOut {
    vec4 worldPos;
    vec3 worldNormal;
    vec3 viewPos;
}vsIn;

float diffuse() {
    return 1.0 / PI;
}

float normal_dist_ggx(float NoH, float a)
{
    float a2 = a * a;
    float denom = ((NoH * NoH * (a2 - 1.0)) + 1.0);
    return a2 / (PI * denom * denom);
}

float visibility_smithggx(float NoV, float NoL, float a)
{
    float a2 = a * a;
    float vv = NoL * sqrt(NoV * NoV * (1.0 - a2) + a2);
    float vl = NoV * sqrt(NoL * NoL * (1.0 - a2) + a2);
    return 0.5 / (vv + vl);
}

vec3 fresnel_schlick(float LoH, vec3 f0, float f90)
{
    return f0 + (vec3(f90) - f0) * pow(1.0 - LoH, 5.0);
}

vec3 specular(vec3 lightDir) {
    vec3 viewDir = normalize(vsIn.viewPos - vec3(vsIn.worldPos));
    vec3 halfDir = normalize(lightDir + viewDir);

    float NoL = clamp(dot(vsIn.worldNormal, lightDir), 0.0, 1.0);
    float NoV = abs(dot(vsIn.worldNormal, viewDir)) + 0.00001;
    float NoH = clamp(dot(vsIn.worldNormal, halfDir), 0.0, 1.0);
    float LoH = clamp(dot(lightDir, halfDir), 0.0, 1.0);

    float rough = max(roughness * roughness, 0.0001);
    vec3 f0 = 0.16 * 0.5 * 0.5 * (1.0 - metallic) + baseColor * metallic;
    float f90 = 1.0;

    return fresnel_schlick(LoH, f0, f90) * normal_dist_ggx(NoH, rough) * visibility_smithggx(NoV, NoL, rough);
}

void main() {
    vec3 lightPos = vec3(-0.5, 1.0, 0.5);
    vec3 lightColor = vec3(1.5, 1.5, 1.5);

    vec3 lightDir = normalize(lightPos);
    float NoL = clamp(dot(vsIn.worldNormal, lightDir), 0.0, 1.0);

    vec3 diffuseColor = (1.0 - metallic) * baseColor * diffuse();
    vec3 specularColor = specular(lightDir);

    vec3 color = (diffuseColor + specularColor) * lightColor * NoL;

    // Tonemapping
    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}
