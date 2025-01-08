#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

// input
layout(location = 0) in vec3 v_normal[];
layout(location = 1) in vec2 v_texCoord[];

// Uniforms
uniform mat4 View;
uniform mat4 Projection;

// centrul modelului in world space
uniform vec4 originalCenter;

uniform float time;        
uniform float gravity;     
uniform float speed; 

layout(location = 0) out vec2 out_texCoord;


void main()
{
    // centrul triunghiului in world space
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 tri_center = (p0 + p1 + p2) / 3.0;


    vec4 explosion_direction = tri_center - originalCenter;
    explosion_direction = normalize(explosion_direction); 

    vec4 v = explosion_direction * speed;
    v.y += speed * 0.5;  

    // calculam noul centru al triunghiului conform legii de miscare:
    float t = time;
    vec3 centerXYZ = tri_center.xyz
                   + v.xyz * t
                   + vec3(0.0, 0.5f * gravity * 2 * t * t, 0.0);

    // oprim la y = 0.0 ca sa nu coboram sub pamant
    if (centerXYZ.y < 0.0) {
        centerXYZ.y = 0.0;
    }

    for (int i = 0; i < 3; i++)
    {
        vec4 oldPos = gl_in[i].gl_Position;
        vec3 localOffset = oldPos.xyz - tri_center.xyz;

        // ca sa pastram, in timpul exploziei, forma archerului
        vec4 finalWorldPos = vec4(centerXYZ + localOffset, 1.0);

        gl_Position = Projection * View * finalWorldPos;

        out_texCoord = v_texCoord[i];

        EmitVertex();

    }

    EndPrimitive();
}
