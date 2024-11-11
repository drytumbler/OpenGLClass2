#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
out vec2 fragmentTexCoord;

out vec3 vertexNormal;

//out vec3 crntPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform vec2 res;
uniform float time;

void main(){
    
  gl_Position = proj * view * model * vec4(vertexPos, 1.0f);
    //fragmentColor = vertexColor;
    
    
    fragmentTexCoord = (vertexPos.xy + 1.0) / 2.0;
    
}

