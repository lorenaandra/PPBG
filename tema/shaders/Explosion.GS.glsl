#version 430

// input
layout(triangles) in;
// Output
layout(triangle_strip, max_vertices = 3) out;

//input
in vec3 vs_worldPos[];
in vec3 vs_worldNormal[];
in vec2 vs_texCoord[];
in float vs_preCurvatureHeight[];
//
// Uniforms
uniform mat4 View;
uniform mat4 Projection;
uniform float time;             
uniform float explosionFactor; 

// output la fragment shader
out vec2 gs_texCoord;
out float gs_preCurvHeight;



void main()
{
    // determin normala la triunghi - v_normal[] are normalele la fiecare vertex
    vec3 avgNormal = normalize(
              vs_worldNormal[0]
            + vs_worldNormal[1]
            + vs_worldNormal[2]
        );


    // puls pt a fi offset factor fata de timp
    float maxTime = 2.0;
    float t = clamp(time, 0.0, maxTime);
    float x = t / maxTime;  
    float pulse =  sin( x * 1.5708 );
    // folosim doar pozitiv
    if (pulse < 0.0) pulse = 0.0;  
    float factor = pulse * explosionFactor;

    // pt fiecare triunghiulet - il mutam cu normala la suprafata
    for (int i = 0; i < 3; i++)
    {
        vec3 originalPos = vs_worldPos[i];
        vec3 explodedPos = originalPos + avgNormal * pulse;

        gl_Position = Projection * View * vec4(explodedPos, 1.0);

        // noua pozitie a triunghiului 
//        vec4 newPos = oldPos + vec4(triNormal * factor, 0.0);
//       
        gs_texCoord = vs_texCoord[i];
        gs_preCurvHeight = vs_preCurvatureHeight[i];
        EmitVertex();
    }

    EndPrimitive();

}
