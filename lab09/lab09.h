#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"


namespace lab
{
    class Lab09 : public gfxc::SimpleScene
    {
     public:
        Lab09();
        ~Lab09();

        void Init() override;

     private:
        void CreateFramebuffer(int width, int height);

        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawObjects(Shader *shader);
        void DrawFramebufferTextures();

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);
        void RenderTextureScreen(Shader *shader, unsigned int textureID);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void LoadShader(const std::string& name);

     private:
        float angle;

        glm::vec3 light_position;
        glm::vec3 light_direction;

        glm::mat4 light_space_view;
        glm::mat4 light_space_projection;
        float light_space_near_plane;
        float light_space_far_plane;

        bool draw_framebuffer_textures;

        unsigned int framebuffer_object;
        unsigned int color_texture;
        unsigned int depth_texture;
    };
}   // namespace lab
