#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int texture_unit;

// Output
out vec2 texture_coord;


void main()
{
	texture_coord = v_texture_coord;
	// preluam noise ul
	float height = texture(texture_2, texture_coord).r;

	vec3 final_pos = vec3(v_position.x, v_position.y + 3 * height, v_position.z);
	gl_Position = Projection * View * Model * vec4(final_pos, 1.0);

}