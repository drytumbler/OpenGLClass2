#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;

in vec3 vertexNormal;
in vec3 crntPos;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;

uniform float scale;
uniform float time;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;



void main(){
    vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
    float alpha = texture(mask, fragmentTexCoord).a;
    
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragmentTexCoord;

    // Time varying pixel color
    vec3 col = vec3(-1.0f) + abs(vec3(2.5 * sin(time) * uv.x, 2.5 * cos(time) * uv.y, normalize(0.5 + uv.x)));

   screenColor = vec4(col, (1.0 - alpha)*(0.75-alpha));
   
}
