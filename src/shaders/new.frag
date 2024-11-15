#version 330 core

in vec2 fragmentTexCoord;

uniform sampler2D sandstone;
uniform sampler2D mask;


void main()
{
    vec3 col = vec3(0.0);
    col += vec3(texture(sandstone, fragmentTexCoord)).rgb;
    float mask = texture(mask, fragmentTexCoord).a;
	col *= mask;
    gl_FragColor = vec4( col, mask); 
}

