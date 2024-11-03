#version 330 core

in vec3 fragmentColor;
in vec2 fragmentTexCoord;

out vec4 screenColor;

uniform sampler2D material;
uniform sampler2D mask;
uniform sampler2D sandstone;

uniform float time;

void main(){

    vec3 baseColor = texture(material, fragmentTexCoord).rgb;
    float alpha = texture(mask, fragmentTexCoord).a;

    //screenColor = vec4(fragmentColor, 1.0);
    // vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
    
    screenColor = vec4(baseColor, (1.0 - alpha)*(0.75-alpha));

}