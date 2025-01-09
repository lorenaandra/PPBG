#version 330 core

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coord;
layout(location = 3) in vec3 v_color;


// Uniforms
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;


uniform sampler2D noise_texture;
uniform float deform_factor;
uniform float curvature_factor;
uniform vec3 helicopter_position;
uniform bool isCircle;


out vec4 pre_curvature_position;   // (x, y+heightmap, z, 1) inainte de curbura
out vec3 fs_color;
out vec4 frag_world_position;

void main()
{
    // transformare la world space
    vec4 world_position = Model * vec4(v_position, 1.0);
    float u;
    float v;
    /* varianta cu copaceii deformati - folosim u si v fiind x si z conform cerintei */
    float scale = isCircle ? 4.0 : 20.0;
    u = (world_position.x / scale) + 0.5;
    v = (world_position.z / scale) + 0.5;

    vec2 uv = vec2(u, v);
//    uv = clamp(uv, 0.0, 1.0); 
    float noise = texture(noise_texture, uv).r;

    /* varianta cu copaceii nedeformati - arata mai bn */
   // float noise = texture(noise_texture, v_tex_coord).r;

    // relief
    float height_offset = deform_factor * noise;
    world_position.y += height_offset;
    vec4 pre_curvature_position = world_position;

    // curvature
    float helper = length(helicopter_position - world_position.xyz);
    float curvature = helper * helper * curvature_factor;
    world_position.y = world_position.y - curvature;

    // ridicam asteroidul pe y+
    world_position.y += 7.0;

    frag_world_position = world_position;

    gl_Position = Projection * View * world_position;


    fs_color = v_color;

}
