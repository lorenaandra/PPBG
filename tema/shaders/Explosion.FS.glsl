#version 330 core

// Inputs coming from geometry stage
in vec2 gs_texCoord;
in float gs_preCurvHeight;

// Uniform textures
uniform sampler2D ground_texture;
uniform sampler2D snow_texture;

// Output color
layout(location = 0) out vec4 out_color;



void main()
{

    vec4 groundColor = texture(ground_texture, gs_texCoord);
    vec4 snowColor   = texture(snow_texture,  gs_texCoord);

    float blendFactor = smoothstep(0.3, 4.0, gs_preCurvHeight);

    out_color = mix(groundColor, snowColor, blendFactor);
}
