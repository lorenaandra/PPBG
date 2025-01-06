#include "lab/lab05/lab05.h"

#include <vector>
#include <iostream>

#include "components/transform.h"
#include "core/engine.h"
#include "utils/gl_utils.h"

#include "lab/lab05/transform3D.h"

using namespace std;
using namespace lab;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab05::Lab05()
{
}


Lab05::~Lab05()
{
}


void Lab05::Init()
{
    color = glm::vec3(0);

    viewport_space = {0, 0, 1280, 720};

    cullFace = GL_BACK;

    // Create a mesh box using custom data
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(0, 1, 0)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0, 1, 1)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 1, 0)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(1, 0, 1)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(1, 1, 1)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 0, 0)),
        };

        vector<unsigned int> indices
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        // Create the mesh from the data
        CreateMesh("cube", vertices, indices);
    }

    ///// al doilea cub
    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(-0.5, -0.5, 0.5), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.5, -0.5, 0.5), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5, 0.5, 0.5), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.5, 0.5, 0.5), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(-0.5, -0.5, -0.5), glm::vec3(1, 0, 0)),
            VertexFormat(glm::vec3(0.5, -0.5, -0.5), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(-0.5, 0.5, -0.5), glm::vec3(0, 0, 0)),
            VertexFormat(glm::vec3(0.5, 0.5, -0.5), glm::vec3(0, 0, 0)),
        };

        vector<unsigned int> indices
        {
            0, 1, 2,    // indices for first triangle
            1, 3, 2,    // indices for second triangle
            2, 3, 7,
            2, 7, 6,
            1, 7, 3,
            1, 5, 7,
            6, 7, 4,
            7, 5, 4,
            0, 4, 1,
            1, 4, 5,
            2, 6, 4,
            0, 2, 4
        };

        // Create the mesh from the data
        CreateMesh("cube2", vertices, indices);
    }


    /// initializari
    lowestPos = 0.0f, highestPos = 3.0f, currentPos = 0.0f;
    moveup = true, scaleup = true;
    currentRotation = 0.0f;
    rotationSpeed = 20.0f;
    currentScale = 1.0f, minScale = 0.5f, maxScale = 2.0f;
    posOx = 0.0f;
    posOy = 0.0f;
    posOz = 0.0f;
}


void Lab05::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // TODO(student): Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    // TODO(student): Create the IBO and bind it
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // TODO(student): Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}


void Lab05::FrameStart()
{

}


void Lab05::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // TODO(student): Set the screen cleaning color. Use the 'color' attribute.
    glClearColor(color.r, color.g, color.b, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static auto camera = new gfxc::Camera();


    ///// pt task 4
    if (currentPos >= highestPos) {
        moveup = false;
    }

    if (currentPos <= lowestPos) {
        moveup = true;
    }

    if (moveup) {
        currentPos += deltaTimeSeconds;
    }
    else {
        currentPos -= deltaTimeSeconds;
    }

    currentRotation += rotationSpeed * deltaTimeSeconds;

    if (currentScale <= minScale) {
        scaleup = true;
    } else if (currentScale >= maxScale) {
        scaleup = false;
    }

    if (scaleup) {
        currentScale += deltaTimeSeconds;
    }
    else {
        currentScale -= deltaTimeSeconds;
    }


    // TODO(student): Draw the objects 4 times in different viewports.
    // Send the 4 cameras with predefined viewing positions and directions to the drawing.

    // stg jos
    viewport_space = transform2D::ViewportSpace(0, 0, 0.75f * resolution.x, 0.5f * resolution.y);
    DrawObjects(GetSceneCamera(), viewport_space);

    // dreapta jos
    camera->SetPositionAndRotation(glm::vec3(0, 3, -3), glm::quatLookAt(glm::normalize(glm::vec3(0, -3, 3)), glm::vec3(0, 1, 0)));
    viewport_space = transform2D::ViewportSpace(0.75f * resolution.x, 0, 0.25f * resolution.x, 0.75f * resolution.y);
    DrawObjects(camera, viewport_space);

    // stg sus
    camera->SetPositionAndRotation(glm::vec3(3, 3, 3), glm::quatLookAt(glm::normalize(glm::vec3(-3, -3, -3)), glm::vec3(0, 1, 0)));
    viewport_space = transform2D::ViewportSpace(0, 0.5f * resolution.y, 0.75f * resolution.x, 0.5f * resolution.y);
    DrawObjects(camera, viewport_space);

    // dreapta sus
    camera->SetPositionAndRotation(glm::vec3(-3, 3, 3), glm::quatLookAt(glm::normalize(glm::vec3(3, -3, -3)), glm::vec3(0, 1, 0)));
    viewport_space = transform2D::ViewportSpace(0.75f * resolution.x, 0.75f * resolution.y, 0.25f * resolution.x, 0.25f * resolution.y);
    DrawObjects(camera, viewport_space);
}


void Lab05::FrameEnd()
{

}

void Lab05::DrawObjects(gfxc::Camera *camera, const transform2D::ViewportSpace & viewport_space)
{
    glm::mat4 view = transform3D::View(
        camera->m_transform->GetWorldPosition(),
        camera->m_transform->GetLocalOZVector(),
        camera->m_transform->GetLocalOXVector(),
        camera->m_transform->GetLocalOYVector()
    );

    glm::mat4 projection = transform3D::Perspective(
        glm::radians(60.0f), (float)viewport_space.width / viewport_space.height, 0.1f, 100.0f
    );

    // TODO(student): Enable face culling
    glEnable(GL_CULL_FACE);

    // TODO(student): Set face custom culling. Use the `cullFace` variable.
    glCullFace(cullFace);

    // TODO(student): Set the position and size of the view port based on the
    // information received from the 'viewport_space' parameter.
    glViewport(viewport_space.x, viewport_space.y, viewport_space.width, viewport_space.height);
    glm::mat4 model;

    model = glm::mat4(1);
    model *= transform3D::Translate(glm::vec3(-1.50f, currentPos, 0));
    model *= transform3D::RotateOX(glm::radians(45.0f));
    model *= transform3D::RotateOZ(glm::radians(-45.0f));
    model *= transform3D::Scale(glm::vec3(0.75f));
    RenderMesh(meshes["cube"], shaders["VertexColor"], model, view, projection);

    model = glm::mat4(1);
    model *= transform3D::Translate(glm::vec3(0, 0.5f, 0));
    model *= transform3D::Scale(glm::vec3(0.75f));
    model *= transform3D::RotateOY(glm::radians(currentRotation));
    RenderMesh(meshes["cube"], shaders["VertexColor"], model, view, projection);

    model = glm::mat4(1);
    model *= transform3D::Translate(glm::vec3(1.5f, 0.5f, 0));
    model *= transform3D::RotateOX(glm::radians(45.0f));
    model *= transform3D::RotateOZ(glm::radians(45.0f));
    model *= transform3D::Scale(glm::vec3(0.5f));
    model *= transform3D::Scale(glm::vec3(currentScale));
    RenderMesh(meshes["cube"], shaders["VertexColor"], model, view, projection);



    ///// task 5
    model = glm::mat4(1);
    model *= transform3D::Translate(glm::vec3(3.0f, 0.5f, 0.0f));
    model *= transform3D::Scale(glm::vec3(0.5f));
    model *= transform3D::Translate(glm::vec3(posOx, posOy, posOz));
    RenderMesh(meshes["cube2"], shaders["VertexColor"], model, view, projection);


    // TODO(student): Disable face culling
    glDisable(GL_CULL_FACE);

    DrawCoordinateSystem(view, projection);
}

void Lab05::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix,
    const glm::mat4 &viewMatrix, const glm::mat4 &projectionMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(viewMatrix));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab05::OnInputUpdate(float deltaTime, int mods)
{
    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.
    //
    // Use the 'window->KeyHold()' and 'window->MouseHold()' methods
    // to check if a certain key or mouse button is pressed.
    //
    // Use the 'deltaTime' parameter to make a movement independent
    // of the number of frames rendered per second. More precisely,
    // when we want to move an object at a speed of 5 units per second,
    // we have:
    //     5 units ... 1 second
    //     x units ... deltaTime seconds
    //
    // Use this association to calculate the number of units of
    // movement at the current frame for a given speed per second.
    //
    // Don't change the position of the object when the position
    // of the camera in the scene changes.
    if (window->MouseHold(GLFW_MOUSE_BUTTON_1)) {
        if (window->KeyHold(GLFW_KEY_W)) {
            posOz -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            posOz += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            posOx -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            posOx += deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            posOy -= deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            posOy += deltaTime;
        }
    }

}


void Lab05::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_R) {
        // TODO(student): Change the values of the color components.
        float r = rand() % 100 / 100.0f;
        float g = rand() % 100 / 100.0f;
        float b = rand() % 100 / 100.0f;
        color.r = r, color.g = g, color.b = b;

    }

    // TODO(student): Switch between GL_FRONT and GL_BACK culling.
    // Save the state in `cullFace` variable and apply it in the
    // `Update()` method, NOT here!
    if (key == GLFW_KEY_F) {
        if (cullFace == GL_FRONT) {
            cullFace = GL_BACK;
        }
        else {
            cullFace = GL_FRONT;
        }
    }
}


void Lab05::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab05::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab05::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab05::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab05::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab05::OnWindowResize(int width, int height)
{
}
