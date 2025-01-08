#version 330 core

in vec4 pre_curvature_position;
in vec3 fs_color;

uniform float objectID; 


layout(location = 0) out vec4 out_color;   // normal color
layout(location = 1) out vec4 outExtra;    // (x, 0, z, ID)

void main()
{
    // normal color
    out_color = vec4(fs_color, 1.0);

    // (worldPosBeforeCurv.x, 0, worldPosBeforeCurv.z, objectID)
    outExtra = vec4(pre_curvature_position.x, 0.0, pre_curvature_position.z, objectID);
}
