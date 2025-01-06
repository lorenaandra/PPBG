#include "lab/tema/tema.h"

#include <vector>
#include <string>
#include <iostream>
#include <stb/stb_image.h>

using namespace std;
using namespace lab;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema::Tema()
{
}


Tema::~Tema()
{
}


void Tema::Init()
{

    auto camera = GetSceneCamera();

    // Relative position of the camera from the helicopter
    glm::vec3 relativeCameraPosition = glm::vec3(0.0f, 12.0f, 3.0f);

    // Rotate the relative position based on the helicopter's rotation (if needed)
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation_oy, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec3 rotatedCameraPosition = glm::vec3(rotationMatrix * glm::vec4(relativeCameraPosition, 1.0f));

    // Set the camera's position relative to the helicopter
    glm::vec3 cameraPosition = helicopterPosition + rotatedCameraPosition;
    camera->SetPosition(cameraPosition);

    // Make the camera look at the helicopter
    camera->SetRotation(glm::quatLookAt(glm::normalize(helicopterPosition - cameraPosition), glm::vec3(0.0f, 1.0f, 0.0f)));


    ///// Load textures
    {
        Texture2D* texture = LoadTexture("src\\lab\\tema\\images\\noise.png");
        mapTextures["noise"] = texture;
    }

    {
        Texture2D* texture = LoadTexture("assets\\textures\\ground.jpg");
        mapTextures["ground"] = texture;
    }

    {
        Texture2D* texture = LoadTexture("src\\lab\\tema\\images\\snow.jpg");
        mapTextures["snow"] = texture;
    }


    ///// Load shaders
    // shader simplu 
    LoadShader("SimpleShader");
    // shader pt deformare - creare forme relief
    LoadShader("Topography");
    // shader pt multi texturare 
    LoadShader("Relief");
    // shader pt creare forma asteroid
    LoadShader("Curvature");



    ///// Load meshes
    { // "panza" alba
        Mesh* mesh = CreateWireframePlane("wireframe", 10.0f, 100);
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = CreateCustomCube("green_cube", 4, glm::vec3(0, 1, 0));
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = CreateCustomCube("maroon_cube", 4, glm::vec3(0.6627f, 0.4784f, 0.3412f));
        meshes[mesh->GetMeshID()] = mesh;
    }


    ///// initializari
    rotation_angle1 = 0.0f;
    rotation_angle2 = 0.0f;

    helicopterPosition = glm::vec3(0.0f, 10.0f, 0.0f);
    rotation_oy = 0.0f;
    rotation_ox = 0.0f;
    speed = 5.0f;
}


void Tema::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // default pentru modul de desenare -> de schimbat in FILL pentru formele de relief
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    auto resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema::Update(float deltaTimeSeconds)
{
    //// planul simplu din triunghiuri (panza)
    //{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    glm::mat4 modelMatrix = glm::mat4(1);
    //    modelMatrix = glm::translate(modelMatrix, glm::vec3(10, 0, 0));
    //    //modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(1, 0, 0));
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.3f));
    //    RenderMesh(meshes["wireframe"], shaders["SimpleShader"], modelMatrix);
    //}

    //// panza reliefata
    //{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //    glm::mat4 modelMatrix = glm::mat4(1);
    //    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5));
    //    modelMatrix = glm::scale(modelMatrix, glm::vec3(1.5f));
    //    RenderSimpleMesh(meshes["wireframe"], shaders["Topography"], modelMatrix, mapTextures["noise"]);
    //}

    //// multi texturare
    //{
    //    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //    glm::mat4 modelMatrix = glm::mat4(1);
    //    modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, -5));
    //    RenderComplexMesh(meshes["wireframe"], shaders["Relief"], modelMatrix, mapTextures["ground"], mapTextures["snow"], mapTextures["noise"]);
    //}

    //// asteroid
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f));
        RenderComplexMesh(meshes["wireframe"], shaders["Curvature"], modelMatrix, mapTextures["ground"], mapTextures["snow"], mapTextures["noise"]);
    }




    /* HELICOPTER */

    glm::mat4 helicopterMatrix = glm::mat4(1.0f);
    helicopterMatrix = glm::translate(helicopterMatrix, helicopterPosition);
    helicopterMatrix = glm::rotate(helicopterMatrix, rotation_oy, glm::vec3(0, 1, 0));
    helicopterMatrix = glm::rotate(helicopterMatrix, rotation_ox, glm::vec3(0, 0, 1));
   // helicopterMatrix = glm::translate(helicopterMatrix, glm::vec3(0.0f, 10.0f, 0.0f));
    helicopterMatrix = glm::scale(helicopterMatrix, glm::vec3(0.5f));

    //// coada elicopter
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, 0.25f, 0.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 0.15f, 0.15f));
        //modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0, 0));
        RenderMesh(meshes["green_cube"], shaders["SimpleShader"], modelMatrix);
    }
    
    // corp elicopter
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;
        modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 0.5f, 0.5f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.5f, 0.5f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderMesh(meshes["green_cube"], shaders["SimpleShader"], modelMatrix);
    }

    rotation_angle1 += deltaTimeSeconds * 360.0f;
    if (rotation_angle1 >= 360.0f) rotation_angle1 -= 360.0f;
    // elice 1
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.525f, 0.25f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-rotation_angle1), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -0.525f, -0.25f));

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.525f, 0.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 0.05f, 0.1f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderMesh(meshes["maroon_cube"], shaders["SimpleShader"], modelMatrix);
    }

    rotation_angle2 += deltaTimeSeconds * 360.0f;
    if (rotation_angle2 >= 360.0f) rotation_angle2 -= 360.0f;

    //// elice 2
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.5f, 0.525f, 0.25f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-rotation_angle2), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.5f, -0.525f, -0.25f));


        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-0.25f, 0.525f, 0.5f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(2.0f, 0.05f, 0.1f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderMesh(meshes["maroon_cube"], shaders["SimpleShader"], modelMatrix);
    }

    // elice coada 1
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;

        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.3125f, 0.25f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-rotation_angle1), glm::vec3(0, 0, 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1, -0.3125f, -0.25f));

        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.25f, 0.0625f, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.25f, 0.25f, 0.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.1f, 0.05f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderMesh(meshes["maroon_cube"], shaders["SimpleShader"], modelMatrix);
    }


    // elice coada 1
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glm::mat4 modelMatrix = helicopterMatrix;

        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1, 0.3125f, 0.25f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(-rotation_angle2), glm::vec3(0, 0, 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1, -0.3125f, -0.25f));


        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.25f, 0.0625f, 0));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.25f, 0.25f, 0.25f));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(90.0f), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.1f, 0.05f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.25f));
        RenderMesh(meshes["maroon_cube"], shaders["SimpleShader"], modelMatrix);
    }



}


void Tema::FrameEnd()
{
    DrawCoordinateSystem();
}


Mesh* lab::Tema::CreateWireframePlane(const std::string& meshName, float planeSize, int divisions)
{
    /* VERTICES */
    std::vector<VertexFormat> vertices;
    std::vector<unsigned int> indices;
    vertices.reserve((static_cast<std::vector<VertexFormat, 
                        std::allocator<VertexFormat>>::size_type>(divisions) + 1) * 
                                        (static_cast<unsigned long long>(divisions) + 1));

    float halfSize = planeSize / 2.0f;
    float distance = planeSize / divisions;

    for (int i = 0; i <= divisions; i++)
    {
        for (int j = 0; j <= divisions; j++)
        { // facem planul pe xoz de dimensiune planeSize -> deci x si z e (-halfSize, +halfSize) ca sa centram planul in 0 0 0
            float x = -halfSize + j * distance;
            float z = -halfSize + i * distance;
            float y = 0.0f;

            glm::vec3 position = glm::vec3(x, y, z);
            glm::vec3 normal = glm::vec3(0, 1, 0);

            // coordonate de textura ca sa putem manipula panza
            float u = (float) j / divisions;
            float v = (float) i / divisions;

            // VertexFormats "texCoord" param
            glm::vec3 color = glm::vec3(1, 1, 1); 
            vertices.push_back(VertexFormat(position, color, normal, glm::vec2(u, v)));
        }
    }

    /* INDICES */
    for (int i = 0; i < divisions; i++) 
    {
        for (int j = 0; j < divisions; j++) 
        {
            int row1 = i * (divisions + 1);
            int row2 = (i + 1) * (divisions + 1);

            int topLeft = row1 + j;
            int topRight = row1 + (j + 1);
            int bottomLeft = row2 + j;
            int bottomRight = row2 + (j + 1);

            //triunghi stanga
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            
            // triunghi dreapta
            indices.push_back(topRight);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
        }
    }

    Mesh* plane = new Mesh(meshName);
    plane->InitFromData(vertices, indices);
    return plane;
}


Mesh* Tema::CreateCustomCube(const std::string& meshName, float sideLength, const glm::vec3& color)
{
    float helper = sideLength / 2.0f;
    glm::vec3 color_front = color;
    glm::vec3 color_back = color;
    glm::vec3 color_left = color;
    glm::vec3 color_right = color;
    glm::vec3 color_top = color;
    glm::vec3 color_bottom = color;

    //color_front = glm::vec3(1.0f, 0.0f, 0.486f);
    //color_back = glm::vec3(0.373f, 1.0f, 0.0f);
    //color_left = glm::vec3(0.0f, 1.0f, 0.706f);
    //color_right = glm::vec3(1.0f, 0.5f, 0.0f);
    //color_top = glm::vec3(0.2f, 0.4f, 0.669f);
    //color_bottom = glm::vec3(0.0f, 0.769f, 1.0f);

    std::vector<VertexFormat> vertices =
    {
        // fata
        VertexFormat(glm::vec3(-helper, -helper,  helper), color_front, glm::vec3(0, 0, 1), glm::vec2(0, 0)),
        VertexFormat(glm::vec3(helper, -helper,  helper), color_front, glm::vec3(0, 0, 1), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(helper,  helper,  helper),  color_front, glm::vec3(0, 0, 1), glm::vec2(1, 1)),
        VertexFormat(glm::vec3(-helper,  helper,  helper),  color_front, glm::vec3(0, 0, 1), glm::vec2(0, 1)),

        // spate
        VertexFormat(glm::vec3(-helper, -helper, -helper), color_back, glm::vec3(0, 0, -1), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(helper, -helper, -helper), color_back, glm::vec3(0, 0, -1), glm::vec2(0, 0)),
        VertexFormat(glm::vec3(helper, helper, -helper), color_back, glm::vec3(0, 0, -1), glm::vec2(0, 1)),
        VertexFormat(glm::vec3(-helper, helper, -helper), color_back, glm::vec3(0, 0, -1), glm::vec2(1, 1)),

        // stanga
        VertexFormat(glm::vec3(-helper, -helper, -helper), color_left, glm::vec3(-1, 0, 0), glm::vec2(0, 0)),
        VertexFormat(glm::vec3(-helper, -helper,  helper), color_left, glm::vec3(-1, 0, 0), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(-helper,  helper,  helper), color_left, glm::vec3(-1, 0, 0), glm::vec2(1, 1)),
        VertexFormat(glm::vec3(-helper,  helper, -helper), color_left, glm::vec3(-1, 0, 0), glm::vec2(0, 1)),

        // dreapta
        VertexFormat(glm::vec3(helper, -helper, -helper), color_right, glm::vec3(1, 0, 0), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(helper, -helper,  helper), color_right, glm::vec3(1, 0, 0), glm::vec2(0, 0)),
        VertexFormat(glm::vec3(helper,  helper,  helper), color_right, glm::vec3(1, 0, 0), glm::vec2(0, 1)),
        VertexFormat(glm::vec3(helper,  helper, -helper), color_right, glm::vec3(1, 0, 0), glm::vec2(1, 1)),

        // sus
        VertexFormat(glm::vec3(-helper,  helper,  helper), color_top, glm::vec3(0, 1, 0), glm::vec2(0, 0)),
        VertexFormat(glm::vec3(helper,  helper,  helper), color_top, glm::vec3(0, 1, 0), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(helper,  helper, -helper), color_top, glm::vec3(0, 1, 0), glm::vec2(1, 1)),
        VertexFormat(glm::vec3(-helper,  helper, -helper), color_top, glm::vec3(0, 1, 0), glm::vec2(0, 1)),

        // jos
        VertexFormat(glm::vec3(-helper, -helper,  helper), color_bottom, glm::vec3(0, -1, 0), glm::vec2(0, 1)),
        VertexFormat(glm::vec3(helper, -helper,  helper), color_bottom, glm::vec3(0, -1, 0), glm::vec2(1, 1)),
        VertexFormat(glm::vec3(helper, -helper, -helper), color_bottom, glm::vec3(0, -1, 0), glm::vec2(1, 0)),
        VertexFormat(glm::vec3(-helper, -helper, -helper), color_bottom, glm::vec3(0, -1, 0), glm::vec2(0, 0))
    };

    std::vector<unsigned int> indices =
    {
        // fata
        0, 1, 2, 2, 3, 0,
        // spate
        4, 5, 6, 6, 7, 4,
        // stanga
        8, 9, 10, 10, 11, 8,
        // dreapta
        12, 13, 14, 14, 15, 12,
        // sus
        16, 17, 18, 18, 19, 16,
        // jos
        20, 21, 22, 22, 23, 20
    };

    Mesh* cubeMesh = new Mesh(meshName);
    cubeMesh->InitFromData(vertices, indices);
    return cubeMesh;
}


Texture2D* Tema::LoadTexture(const char* imagePath)
{
    int width, height, channels;
    unsigned char* imageData = stbi_load(imagePath, &width, &height, &channels, 0);

    return CreateTexture(width, height, channels, imageData);
}


// functie refolosita din lab 8
Texture2D* Tema::CreateTexture(unsigned int width, unsigned int height,
    unsigned int channels, unsigned char* data)
{
    GLuint textureID = 0;
    unsigned int size = width * height * channels;

    // TODO(student): Generate and bind the new texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (GLEW_EXT_texture_filter_anisotropic) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 4);
    }
    // TODO(student): Set the texture parameters (MIN_FILTER and MAG_FILTER) using glTexParameteri
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    CheckOpenGLError();


    // TODO(student): Use the "glTexImage2D" directive to load the information
    // into the graphics processor's memory. Use the correct format based on
    // the number of components:
    //   - 1 color channel - GL_RED
    //   - 2 color channels - GL_RG
    //   - 3 color channels - GL_RGB
    //   - 4 color channels - GL_RGBA
    GLint param1;
    GLenum param2;
    switch (channels) {
    case 1:
        param1 = param2 = GL_RED; break;
    case 2:
        param1 = param2 = GL_RG; break;
    case 3:
        param1 = param2 = GL_RGB; break;
    case 4:
        param1 = param2 = GL_RGBA; break;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, param1, width, height, 0, param2, GL_UNSIGNED_BYTE, data);


    // TODO(student): Generate texture mip-maps
    glGenerateMipmap(GL_TEXTURE_2D);

    CheckOpenGLError();

    // Save the texture into a wrapper Texture2D class for using easier later during rendering phase
    Texture2D* texture = new Texture2D();
    texture->Init(textureID, width, height, channels);

    SAFE_FREE_ARRAY(data);
    return texture;
}


// functie refolosita din lab 8 - functioneaza pt 2 texturi
void Tema::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1, Texture2D* texture2)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model matrix
    GLint loc_model_matrix = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    int loc_view_matrix = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    int loc_projection_matrix = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // TODO(student): Set any other shader uniforms that you need
    int elapsedTime = glGetUniformLocation(shader->program, "elapsedTime");
    glUniform1f(elapsedTime, Engine::GetElapsedTime());

    if (texture1)
    {
        // TODO(student): Do these:
        // - activate texture location 0
        // - bind the texture1 ID
        // - send theuniform value
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_unit"), 0);
        glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);

    }

    if (texture2)
    {
        // TODO(student): Do these:
        // - activate texture location 1
        // - bind the texture2 ID
        // - send the uniform value
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "texture_unit"), 1);
        glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);

    }

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


// functie modificata - 3 texturi
void Tema::RenderComplexMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* groundTexture, Texture2D* snowTexture, Texture2D* noiseTexture)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // Bind model, view, and projection matrices
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Model"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "View"), 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetViewMatrix()));
    glUniformMatrix4fv(glGetUniformLocation(shader->program, "Projection"), 1, GL_FALSE, glm::value_ptr(GetSceneCamera()->GetProjectionMatrix()));

    // Bind ground texture to texture unit 0
    if (groundTexture)
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, groundTexture->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "ground_texture"), 0);
    }

    // Bind snow texture to texture unit 1
    if (snowTexture)
    {
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, snowTexture->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "snow_texture"), 1);
    }

    // Bind noise texture to texture unit 2
    if (noiseTexture)
    {
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, noiseTexture->GetTextureID());
        glUniform1i(glGetUniformLocation(shader->program, "noise_texture"), 2);
    }


    GLint deformFactor = glGetUniformLocation(shader->program, "deform_factor");
    glUniform1f(deformFactor, 5.5f);

    // curvature_factor
    GLint locCurv = glGetUniformLocation(shader->program, "curvature_factor");
    //glUniform1f(locCurv, 0.07f);
    glUniform1f(locCurv, 0.08f);

    // helicopter_position
    GLint locHeli = glGetUniformLocation(shader->program, "helicopter_position");
    glUniform3f(locHeli, 0.0f, 0.0f, 0.0f);

    // Draw the mesh
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


void Tema::LoadShader(const std::string& name)
{
    std::string shaderPath = PATH_JOIN(window->props.selfDir, "src/lab", "Tema", "shaders");

    // Create a shader program
    {
        Shader* shader = new Shader(name);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".VS.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(shaderPath, name + ".FS.glsl"), GL_FRAGMENT_SHADER);

        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {

        if (window->KeyHold(GLFW_KEY_W)) {
            helicopterPosition.z -= speed * deltaTime;  // move forward in negative Z
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            helicopterPosition.z += speed * deltaTime;  // move backward
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            helicopterPosition.x -= speed * deltaTime;  // move left
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            helicopterPosition.x += speed * deltaTime;  // move right
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            helicopterPosition.y -= speed * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            helicopterPosition.y += speed * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_LEFT)) {
            rotation_oy += 1.5f * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_RIGHT)) {
            rotation_oy -= 1.5f * deltaTime;
        }

        if (window->KeyHold(GLFW_KEY_UP)) {
            rotation_ox += 1.5f * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_DOWN)) {
            rotation_ox -= 1.5f * deltaTime;
        }

    }
}


//void Tema::UpdateCamera()
//{
//    auto camera = GetSceneCamera();
//
//    // Adjust the relative position as needed
//    glm::vec3 relativeCameraPosition = glm::vec3(0.0f, 2.0f, -5.0f);
//
//    // Rotate the relative position based on helicopter's rotation
//    glm::vec3 rotatedCameraPosition = glm::vec3(
//        glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 1, 0)) * glm::vec4(relativeCameraPosition, 1.0f)
//    );
//
//    // Set camera position and orientation
//    camera->SetPosition(helicopterPosition + rotatedCameraPosition);
//
//    // Camera looks at the helicopter
//    camera->SetRotation(glm::quatLookAt(glm::normalize(helicopterPosition - camera->m_transform->GetWorldPosition()), glm::vec3(0, 1, 0)));
//}


void Tema::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema::OnWindowResize(int width, int height)
{
}