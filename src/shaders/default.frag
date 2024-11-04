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


void main() {
    vec3 baseColor = texture(sandstone, fragmentTexCoord).rgb;
    float alpha = texture(mask, fragmentTexCoord).a;

    // Calculate the light direction
    vec3 toLight = normalize(lightPos - crntPos);
    float diff = max(dot(vertexNormal, toLight), 0.0);

    // Ambient light
    float ambientStrength = 0.1; // Adjust this value as needed
    vec3 ambient = ambientStrength * lightColor.rgb;

    // Calculate the final color
    vec3 finalColor = baseColor * (ambient + diff * lightColor.rgb);
    
    // Final output color
    screenColor = vec4(finalColor, (1.0 - alpha) * (0.75 - alpha));
}
