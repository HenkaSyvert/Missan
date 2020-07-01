#pragma once

#include <glm/glm.hpp>

#include <vector>

namespace missan {

    class Transform {
    public:
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 rotationDeg = glm::vec3(0, 0, 0);
        glm::vec3 scale = glm::vec3(1, 1, 1);
       
        glm::mat4 GetMatrix();

        glm::vec3 GetBackwardVector();
        glm::vec3 GetRightVector();
        glm::vec3 GetUpVector();

        

    };


}