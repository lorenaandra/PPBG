#version 330
#extension GL_ARB_separate_shader_objects : enable
// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_tex_coord;
layout(location = 3) in vec3 v_color;


// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float app_time;

// Output
// TODO(student): Output values to fragment shader
out vec3 color;

void main()
{
    // TODO(student): Send output to fragment shader
    color = v_color;
    color.x = sin(app_time);

    // TODO(student): Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position * sin(app_time), 1.0);

}