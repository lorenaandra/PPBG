#version 430

// input
layout(triangles) in;
// Output
layout(triangle_strip, max_vertices = 3) out;

//input
layout(location = 0) in vec3 gs_worldPos[];
layout(location = 1) in vec3 v_normal[];
layout(location = 2) in vec2 v_texCoord[];
layout(location = 3) in float gs_precurv_height[];

// Uniforms
uniform mat4 View;
uniform mat4 Projection;
uniform float time;             
uniform float explosionFactor; 
uniform float explosionCenter;

// output la fragment shader
layout(location = 0) out vec2 out_texCoord;
layout(location = 1) out float out_precurv_height;

void main()
{
    // determin normala la triunghi - v_normal[] are normalele la fiecare vertex
//    vec3 c1 = gs_worldPos[0];
//    vec3 c2 = gs_worldPos[1];
//    vec3 c3 = gs_worldPos[2];
//    vec3 expl_centroid = (c1 + c2 + c3) / 3.0 ;
//
//  //  vec3 offset_dir = normalize(expl_centroid - explosionCenter);

    vec3 trinormal = normalize(v_normal[0] + v_normal[1] + v_normal[2]);
    vec3 offset_dir = trinormal;
    
    // puls pt a fi offset factor fata de timp
//    float pulse = sin(time);
//    // folosim doar pozitiv
//    if (pulse < 0.0) pulse = 0.0;  
//    float factor =  explosionFactor;
//    

//    float x = clamp(time, 0.0, 3.0) / 3.0;
//    float factor = explosionFactor * (1.0 - exp(-5.0 * x)); 
//
//
    // pt fiecare triunghiulet - il mutam cu normala la suprafata
    for (int i = 0; i < 3; i++)
    {
        vec4 oldPos = gl_in[i].gl_Position;    
        // noua pozitie a triunghiului 
        vec4 newPos = oldPos + vec4(offset_dir, 0.0) * explosionFactor;
       
        gl_Position = Projection * View * newPos;

        // GS -> FS
        out_texCoord = v_texCoord[i];

        out_precurv_height = gs_precurv_height[i];

        EmitVertex();
    }

    EndPrimitive();

}
