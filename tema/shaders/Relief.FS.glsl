#version 330

// Input 
in vec2 texture_coord;
in float vertex_height;

// Uniform properties
uniform sampler2D ground_texture;
uniform sampler2D snow_texture;

// Output color
layout(location = 0) out vec4 out_color;

void main()
{

    vec4 ground_color = texture(ground_texture, texture_coord);
    vec4 snow_color = texture(snow_texture, texture_coord);

    float blend_factor = smoothstep(1.0, 2.0, vertex_height); 

    vec4 mix_color = mix(ground_color, snow_color, blend_factor);

    out_color = mix_color;
}
