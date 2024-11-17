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
  vec2 tex = fragmentTexCoord;
  vec3 baseColor =  texture(beach1, tex).rgb;
  vec3 beachNormals =  texture(beach3, tex).rgb;
  vec3 beachMask =  texture(beach2, tex).rgb;
  float diffuse = max(0.0, dot(normalize(lightPos), fragmentNormals * beachNormals * beachMask));

  gl_FragColor = vec4(vec3(baseColor) * (.1 + diffuse), 1.0);
}
