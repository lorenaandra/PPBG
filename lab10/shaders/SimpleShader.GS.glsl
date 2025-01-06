#version 430

// Input and output topologies
layout(triangles) in;
layout(triangle_strip, max_vertices = 100) out;

// Input
layout(location = 1) in vec2 v_texture_coord[];

// Uniform properties
uniform mat4 View;
uniform mat4 Projection;
// TODO(student): Declare other uniforms here
const float offset_step = 2;

// Output
layout(location = 0) out vec2 texture_coord;

void main()
{
	// TODO(student): Emit the vertices of the triangle for which
	// information is received in the input attributes. Set the
	// following information for each vertex:
	//   - The coordinate of the vertex in clip space, transformed
	//     from world space, as received from the vertex shader
	//   - Texture coordinate received from the vertex shader.


	//TASK 1
	for (int i = 0; i < 3; ++i) {

        texture_coord = v_texture_coord[i];
        gl_Position = Projection * View * gl_in[i].gl_Position;
        EmitVertex();
    }
    EndPrimitive();



}
