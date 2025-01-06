#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform sampler2D noise_texture;

// Output
out vec2 texture_coord;
out float vertex_height;

void main()
{
    // fetch noise
    float height = texture(noise_texture, v_texture_coord).r;
    vec3 final_pos = vec3(v_position.x, v_position.y + 3.0 * height, v_position.z);

    // pt fragment shader pt imbinare texturi: (u, v) si inaltimea formata cu noise
    texture_coord = v_texture_coord;
    vertex_height = height * 3.0;

    gl_Position = Projection * View * Model * vec4(final_pos, 1.0);
}
