#version 430

// input
layout(triangles) in;
// Output
layout(triangle_strip, max_vertices = 3) out;

//input
layout(location = 0) in vec3 v_normal[];
layout(location = 1) in vec2 v_texCoord[];

// Uniforms
uniform mat4 View;
uniform mat4 Projection;
uniform float time;             
uniform float explosionFactor; 

// output la fragment shader
layout(location = 0) out vec2 out_texCoord;

void main()
{
    // determin normala la triunghi - v_normal[] are normalele la fiecare vertex
    vec3 triNormal = normalize(v_normal[0] + v_normal[1] + v_normal[2]);

    // puls pt a fi offset factor fata de timp
    float pulse = sin(time);
    // folosim doar pozitiv
    if (pulse < 0.0) pulse = 0.0;  
    float factor = pulse * explosionFactor;

    // pt fiecare triunghiulet - il mutam cu normala la suprafata
    for (int i = 0; i < 3; i++)
    {
        vec4 oldPos = gl_in[i].gl_Position;    
        // noua pozitie a triunghiului 
        vec4 newPos = oldPos + vec4(triNormal * factor, 0.0);
       
        gl_Position = Projection * View * newPos;
        out_texCoord = v_texCoord[i];

        EmitVertex();
    }

    EndPrimitive();

}
