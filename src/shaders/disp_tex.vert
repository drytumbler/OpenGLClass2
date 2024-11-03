#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texPos;

out vec3 fragmentColor;
out vec2 fragmentTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


uniform float time;

uniform mat3 normalMatrix;

void main(){
    gl_Position =proj * view * model * vec4(vertexPos, 1.0f);
    fragmentTexCoord = vec2(texPos.x, texPos.y);
}