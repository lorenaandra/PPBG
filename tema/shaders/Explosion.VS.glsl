#version 410


// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// VS -> GS
layout(location = 0) out vec3 vs_worldPos;
layout(location = 1) out vec3 vs_normal;
layout(location = 2) out vec2 vs_texcoord;
layout(location = 3) out float out_pre_curvature_height;



// Uniform properties
uniform mat4 Model;


uniform vec3 helicopter_position;
uniform float deform_factor;
uniform float curvature_factor;
uniform sampler2D noise_texture;




void main()
{
    // transformare la world space
    vec4 worldPos = Model * vec4(v_position, 1.0);
   // vec3 world_position = worldPos.xyz;

    // relief
    float noise = texture(noise_texture, v_texture_coord).r;
    worldPos.y = worldPos.y + deform_factor * noise;

    // height pentru aplicare de zapada in fs
    float pre_curvature_height = worldPos.y;

    // curvature - formule cerinta
    float helper = length(helicopter_position - worldPos.xyz);
    float curvature = helper * helper * curvature_factor;
    worldPos.y = worldPos.y - curvature;

    // ridicam asteroidul pe y+
    worldPos.y += 7.0;

    gl_Position = worldPos;

    vs_worldPos = worldPos.xyz;
    vs_normal = mat3(Model) * v_normal;
    vs_texcoord = v_texture_coord;
    out_pre_curvature_height = pre_curvature_height;

    
    //texture_coord = v_texture_coord;
}
