#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "gameobject.hpp"
#include "shaderprogram.hpp"
#include "camera.hpp"
#include "scene.hpp"

#include "mesh.hpp"
#include "collider.hpp"

namespace missan {

    class Renderer {

    private:
        Camera* camera_ptr = nullptr;
        ShaderProgram* shader_ptr = nullptr;

        glm::vec4 clearColor = { 0.1f, 0.1f, 0.1f, 1.0f };

    public:
        Renderer(ShaderProgram& shader, Camera& camera);

        void Prepare();
        void SetClearColor(glm::vec4 color);

        void Render(GameObject& go);
        void Render(const std::vector<GameObject*>& gos);
        void Render(Scene& scene);
        void RenderCollider(Collider& collider);

        void SetCamera(Camera& camera);
        void SetShader(ShaderProgram& shader);

    };

}