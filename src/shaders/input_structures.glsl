layout(set = 0, binding = 0) uniform SceneData {
    mat4 view;
    mat4 proj;
    mat4 viewProj;
    vec4 ambientColor;
    vec4 sunlightDirection; // w for power
    vec4 sunlightColor;
} sceneData;

layout(set = 1, binding = 0) uniform MaterialData {
    vec4 colorFactors;
    vec4 metalRoughFactors;
} materialData;

layout(set = 1, binding = 1) uniform sampler2D colorTex;
layout(set = 1, binding = 2) uniform sampler2D metalRoughTex;

layout(set = 2, binding = 0) uniform ObjectData {
    mat4 model;
} objectData;