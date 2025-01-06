#version 330

// Input
in vec2 texture_coord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform int texture_unit;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
	vec4 color; 
	// pt ground:
	vec4 color1 = texture(texture_1, texture_coord);
	// pt relief:
	vec4 color2 = texture(texture_2, texture_coord);

	out_color = vec4(1, 1, 1, 1);
	
}