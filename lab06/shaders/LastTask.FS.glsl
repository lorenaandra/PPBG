#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 color;

// Output
out vec4 out_color;


void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(color, 1);

}
