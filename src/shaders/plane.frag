#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;

in vec3 fragmentNormals;
in vec3 crntPos;

uniform sampler2D beach1;
uniform sampler2D beach2;
uniform sampler2D beach3;

uniform float scale;
uniform float time;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform vec3 camDir;

void main(){
  vec3 baseColor =  texture(beach1, fragmentTexCoord).rgb;


  gl_FragColor = vec4(vec3(baseColor), 1.0);
}
