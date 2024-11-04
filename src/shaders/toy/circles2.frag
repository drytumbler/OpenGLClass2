#version 330 core

#define  red		vec3(1.0, 0.0, 0.0)
#define  green		vec3(0.17, 1.0, 0.2)
#define  blue  	       	vec3(0.0, 0.0, 1.0)
#define  yellow	       	vec3(1.0, 1.0, 0.0)
#define  magenta       	vec3(1.0, 0.0, 1.0)
#define  cyan       	vec3(0.0, 1.0, 1.0)
#define  white       	vec3(1.0, 1.0, 1.0)
#define  black		vec3(0.0, 0.0, 0.0)

#define SHARPNESS 0.005


in vec3 fragmentColor;
in vec2 fragmentTexCoord;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;

uniform float time;
uniform vec2 res;


float Circle (vec2 p, float r, float blur){
  float dC = length(p) - r;
  float c = smoothstep(blur, - blur, dC);
  return c;
}

void main(){
  vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
  float alpha = texture(mask, fragmentTexCoord).a;
  
  // Normalized pixel coordinates (from 0 to 1)
  vec2 uv = gl_FragCoord.xy / res;
  uv -= 0.5;
  //uv *= 2.0;
  uv.x *= res.x / res.y;

  vec3 col = vec3(uv.x, uv.y, 0.0);

  float d = length(uv);
  float r = 0.05 * sin(time) + 0.50;
  vec2 center = vec2(0.2 * sin(time), 0.1 * cos(time));
    
  float c = Circle(uv + center * 0.333, r, 0.05);
  float c2 = Circle(uv + center * 0.666 , r, 0.05);
  float c3 = Circle(uv + center, r, 0.05);
  //  c2 = c2 > 0 ? 1.0 : 0.0;
  
  //screenColor = vec4(vec3(c, c2, c3) * 0.2 * baseColor + baseColor * 0.8, 1.0f);
  float baseLight = 0.150;
  //float baseLight = 0.50;
  float spotLight = 0.850;
  //float spotLight = 0.50;
  //screenColor = vec4((vec3(c, c2, c3) + baseLight) * spotLight * baseColor, 1.0f);
  screenColor = vec4((vec3(c, c2, c3) + baseLight) * spotLight * baseColor, 1.0f);

  screenColor = pow(screenColor, vec4(1.1));


  float c4 = Circle(uv, 0.15, 0.01);

  //screenColor += c4;
}
