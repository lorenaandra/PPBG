#version 330


// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 helicopter_position;
uniform float deform_factor;
uniform float curvature_factor;
uniform sampler2D noise_texture;


// Output
out vec2 texture_coord;
out float pre_curvature_height;



void main()
{
    // transformare la world space
    vec4 worldPos = Model * vec4(v_position, 1.0);
    vec3 world_position = worldPos.xyz;

    // relief
    float noise = texture(noise_texture, v_texture_coord).r;
    world_position.y = world_position.y + deform_factor * noise;

    // height pentru aplicare de zapada in fs
    pre_curvature_height = world_position.y;

    // curvature - formule cerinta
    float helper = length(helicopter_position - world_position);
    float curvature = helper * helper * curvature_factor;
    world_position.y = world_position.y - curvature;

    // ridicam asteroidul pe y+
    world_position.y += 7.0;

    gl_Position = Projection * View * vec4(world_position, 1.0);

    // pt fragment shader
    texture_coord = v_texture_coord;
}
