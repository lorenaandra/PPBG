#version 330 core

in vec4 pre_curvature_position;
in vec3 fs_color;
in vec4 frag_world_position;

uniform float objectID; 


layout(location = 0) out vec4 out_color;   // normal color
layout(location = 1) out vec4 outExtra;    // (x, 0, z, ID)
layout(location = 2) out vec3 out_world_position;


void main()
{
    // normal color
    out_color = vec4(fs_color, 1.0);

    outExtra = vec4(pre_curvature_position.x, 0.0, pre_curvature_position.z, objectID);

    out_world_position = frag_world_position.xyz;
}
