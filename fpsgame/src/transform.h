#pragma once

#include <glm/glm.hpp>

namespace missan {

    class Transform {

    public:
        glm::vec3 position = glm::vec3(0, 0, 0);
        glm::vec3 rotation = glm::vec3(0, 0, 0);
        glm::vec3 scale = glm::vec3(1, 1, 1);

        glm::mat4 GetMatrix();

    };

}