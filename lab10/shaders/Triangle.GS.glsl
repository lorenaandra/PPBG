#version 430

// Input and output topologies
layout(triangles) in;
layout(triangle_strip, max_vertices = 12) out;

// Uniform properties
uniform mat4 View;
uniform mat4 Projection;
// TODO(student): Declare other uniforms here

// Output
layout(location = 0) out vec3 color;

void EmitPoint(vec3 position, vec3 c)
{
    color = c;
    gl_Position = Projection * View * vec4(position, 1);
    EmitVertex();
}


void EmitTriangle(vec3 v1, vec3 v2, vec3 v3, vec3 c1, vec3 c2, vec3 c3)
{
    EmitPoint(v1, c1);
    EmitPoint(v2, c2);
    EmitPoint(v3, c3);
    EndPrimitive();
}

void main()
{
    vec3 p1 = gl_in[0].gl_Position.xyz;
    vec3 p2 = gl_in[1].gl_Position.xyz;
    vec3 p3 = gl_in[2].gl_Position.xyz;
    // TODO(student): Emit the vertices of the triangle for which
    // information is received in the input attributes. Use EmitPoint()
    // and set a color information associated with each vertex.

    // culori si mijlocuri
    vec3 red    = vec3(1.0, 0.0, 0.0);
    vec3 green  = vec3(0.0, 1.0, 0.0);
    vec3 blue   = vec3(0.0, 0.0, 1.0);
    vec3 yellow = vec3(1.0, 1.0, 0.0);

    vec3 mid12  = (p1 + p2) / 2.0;
    vec3 mid23  = (p2 + p3) / 2.0;
    vec3 mid31  = (p3 + p1) / 2.0;
    vec3 center = (p1 + p2 + p3) / 3.0;


    // (1) Triangle formed by p1, mid12, mid31
    // p1 e stanga sus, p2 e dreapta sus, p3 e jos
    EmitTriangle(p1, mid12, mid31, red, yellow, yellow);

    // (2) Triangle formed by p2, mid23, mid12
    EmitTriangle(p2, mid23, mid12, red, yellow, yellow);

    // (3) Triangle formed by p3, mid31, mid23
    EmitTriangle(p3, mid31, mid23, red, yellow, yellow);

    // (4) The innermost triangle formed by mid12, mid23, mid31
    EmitTriangle(mid12, mid23, mid31, yellow, yellow, yellow);

}
