#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "gameobject.h"
#include "shaderprogram.h"
#include "camera.h"
#include "scene.h"

namespace missan {

    class Renderer {

    private:
        Camera* camera_ptr = nullptr;
        ShaderProgram* shader_ptr = nullptr;

    public:
        Renderer(ShaderProgram& shader, Camera& camera);

        void Prepare();

        void Render(GameObject& go);
        void Render(std::vector<GameObject>& gos);
        void Render(Scene& scene);

        void SetCamera(Camera& camera);

        void SetShader(ShaderProgram& shader);

    };

}