#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 texPos;
layout (location = 3) in vec3 vertexNormals;

out vec3 fragmentColor;
out vec2 fragmentTexCoord;

out vec3 vertexNormal;

out vec3 crntPos;

uniform mat4 model;
//uniform mat4 view;
//uniform mat4 proj;

uniform mat4 camMatrix;

uniform float time;
uniform float scale;


uniform mat3 normalMatrix;

void main(){
     crntPos = vec3(model * vec4(vertexPos, 1.0f));
    gl_Position = camMatrix * vec4(crntPos, 1.0f);
    //fragmentColor = vertexColor;
    //fragmentColor = colors[gl_VertexID];
    //fragmentTexCoord = vec2(0.25 * scale, 0.25 * scale) * (texPos + vertexPos.xy + vec2(2.0));
    fragmentTexCoord = texPos;
    vertexNormal = normalize(normalMatrix * vertexNormals);
}