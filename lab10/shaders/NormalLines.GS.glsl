#version 430

layout(triangles) in;
layout(line_strip, max_vertices = 6) out; 
// we can draw 3 lines = 3 pairs => 6 vertices max per input triangle

layout(location = 0) in vec3 v_normal[];
layout(location = 1) in vec2 v_texCoord[];

uniform mat4 View;
uniform mat4 Projection;
uniform float normalLength;  


layout(location = 0) out vec3 out_color;

void main()
{

    for (int i = 0; i < 3; i++) {
        // start point of the line: the vertex itself
        vec4 startPosEye = View * gl_in[i].gl_Position;

        // end point: startPosEye + normal * normalLength
        vec3 normDir = normalize(v_normal[i]);
        vec4 endPosEye = startPosEye + vec4(normDir * normalLength, 0.0);

        // *** Emit the line from startPos -> endPos in eye space => then Project ***

        // 1) start
        gl_Position = Projection * startPosEye;
        out_color = vec3(0, 0, 1);
        EmitVertex();

        // 2) end
        gl_Position = Projection * endPosEye;
        out_color = vec3(0, 0, 1);
        EmitVertex();

        // end the line segment
        EndPrimitive();  // end this line segment
    }
}
