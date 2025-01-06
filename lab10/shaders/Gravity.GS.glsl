#version 430

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

// input
layout(location = 0) in vec3 v_normal[];
layout(location = 1) in vec2 v_texCoord[];

// Uniforms
uniform mat4 View;
uniform mat4 Projection;

// center of the model in world space
uniform vec4 modelCenter;

uniform float time;        // how long since explosion started
uniform float gravity;     
uniform float initialSpeed; // outward & upward velocity

layout(location = 0) out vec2 out_texCoord;


void main()
{
    // for each input triangle, we first find its center in world space:
    vec4 p0 = gl_in[0].gl_Position;
    vec4 p1 = gl_in[1].gl_Position;
    vec4 p2 = gl_in[2].gl_Position;
    vec4 triCenter = (p0 + p1 + p2) / 3.0;

    // Outward direction from modelCenter to triCenter
    vec4 dir = triCenter - modelCenter;
    dir = normalize(dir);  // direction only

    // For simplicity, define velocity in world space:
    //   v = initialSpeed * dir + (0, someUp, 0)
    // You can tune the upward portion as you like:
    vec4 velocity = dir * initialSpeed;
    velocity.y += initialSpeed * 0.5;  // push up half as strongly

    // Now the parametric eqn in world space:
    //   position(t) = triCenter + velocity*t + 1/2 * (0, gravity, 0)*t^2

    // calculam noul centru al triunghiului conform legii de miscare:
    float t = time;
    vec3 centerXYZ = triCenter.xyz
                   + velocity.xyz * t
                   + vec3(0.0, 0.5f * gravity * t * t, 0.0);

    // stop y at 0 so triangles dont go bellow the ground
    if (centerXYZ.y < 0.0) {
        centerXYZ.y = 0.0;
    }

    // For each vertex i, we keep the local offset from triCenter
    // so the triangle shape remains intact
    for (int i = 0; i < 3; i++)
    {
        vec4 oldPos = gl_in[i].gl_Position;
        vec3 localOffset = oldPos.xyz - triCenter.xyz;

        // The new position is the centerXYZ plus that local offset
        vec4 finalWorldPos = vec4(centerXYZ + localOffset, 1.0);

        gl_Position = Projection * View * finalWorldPos;

        out_texCoord = v_texCoord[i];

        EmitVertex();

    }

    EndPrimitive();
}
