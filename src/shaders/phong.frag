#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;
in vec3 vertexNormal;
in vec3 crntPos;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;
uniform sampler2D sandstone1;
uniform sampler2D sandstone2;
uniform sampler2D sandstone3;

uniform float scale;
uniform float time;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform vec3 camDir;

void main() {
  vec2 tex = 2.6 * fragmentTexCoord;
  
  // ambient
  vec3 ambientColor = vec3(1.0, 1.0, 1.0) * (0.5 + 0.5*sin(time * 0.25));
  float ambientStrength = 0.25 * (0.5 + 0.5*sin(time * 0.25));
  vec3 ambient = ambientColor * ambientStrength;
  // diffuse
  vec3 roughnessT = texture(sandstone2, tex).rgb;
  vec3 normalT = normalize(texture(sandstone3, tex).rgb);
  vec3 normal = normalize(vertexNormal.xyz);

  //if(fract(time*.1) > .5)
  normal *= normalT;
  float diffuseStrength;
  // if (fract(time * 0.025) > 0.5)
    diffuseStrength = max(0.0, dot(normalize(lightPos * roughnessT), normal));
    // else
    // diffuseStrength = max(0.0, dot(normalize(lightPos), normal));
  vec3 diffuse = diffuseStrength * lightColor.rgb;
  // specular
  vec3 reflection = normalize(reflect(-lightPos, normal));
  float specularStrength = max(0.0, dot(normalize(camPos), reflection));
  specularStrength = pow(specularStrength, 2);
  vec3 specular = specularStrength * lightColor.rgb;
  
  // lighting = ambient + diffuse + specular
  vec3 lighting = ambient + diffuse;
  

  vec3 modelColor = texture(sandstone1, tex).rgb;
  //vec3 modelColor = vec3(1.0, 0.6, 0.3);
  vec3 finalColor = modelColor * lighting;
  
  gl_FragColor = vec4(modelColor*lighting, 1.0);
}