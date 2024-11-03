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

    //screenColor = vec4(fragmentColor, 1.0);

    vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
    //baseColor *= texture(material, fragmentTexCoord).rgb;
    //baseColor *= baseColor;
    float alpha = texture(mask, fragmentTexCoord).a;


    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragmentTexCoord;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(uv.xyx+vec3(0,2,4));

  
    vec3 toLight = normalize(lightPos - crntPos);
    float diff = max(dot(vertexNormal, toLight), 0.0f);

    //col = fragmentTexCoord.y * vec3(1.0, .0, .0);
    col *= (diff + 0.2);
    screenColor = vec4(baseColor * diff, (1.0 - alpha)*(0.75-alpha));

  // Output to screen
   // screenColor = vec4(col,1.0);
   // screenColor = baseColor;
}