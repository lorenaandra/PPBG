#pragma once

#include <string>
#include <unordered_map>

#include "components/simple_scene.h"
#include "components/transform.h"


namespace lab
{
    class Tema : public gfxc::SimpleScene
    {
    public:
        Tema();
        ~Tema();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        Texture2D* CreateTexture(unsigned int width, unsigned int height, unsigned int channels, unsigned char* data);
        void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        //void UpdateCamera();

        void LoadShader(const std::string& name);
        Texture2D* LoadTexture(const char* imagePath);
        Mesh* CreateWireframePlane(const std::string& meshName, float planeSize, int divisions);
        void RenderComplexMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, Texture2D* groundTexture, Texture2D* snowTexture, Texture2D* noiseTexture);
        Mesh* CreateCustomCube(const std::string& meshName, float sideLength, const glm::vec3& color);


        std::unordered_map<std::string, Texture2D*> mapTextures;
        float rotation_angle1;
        float rotation_angle2;
        glm::vec3 helicopterPosition;
        float speed;
        float rotation_oy;
        float rotation_ox;

    };
}   // namespace lab
