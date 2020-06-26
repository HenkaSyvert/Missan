#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gameobject.h"
#include "shaderprogram.h"

namespace missan {

    class Renderer {

    private:
        glm::mat4 projMat;
        Transform* camera_ptr = nullptr;
        ShaderProgram* shader_ptr = nullptr;

    public:
        void Prepare();

        void Render(GameObject& go);

        void SetProjection(glm::mat4 projMat);

        void SetCamera(Transform& camera);

        void SetShader(ShaderProgram& shader);

    };

}