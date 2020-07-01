#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "gameobject.h"
#include "shaderprogram.h"
#include "camera.h"

namespace missan {

    class Renderer {

    private:
        Camera* camera_ptr = nullptr;
        ShaderProgram* shader_ptr = nullptr;

    public:
        void Prepare();

        void Render(GameObject& go);
        void Render(std::vector<GameObject>& gos);

        void SetCamera(Camera& camera);

        void SetShader(ShaderProgram& shader);

    };

}