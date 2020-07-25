#pragma once

#include "components/component.hpp"

#include <glm/glm.hpp>

namespace missan {

    class Transform : public Component{

    private:

    public:
        Transform* Clone() const { return new Transform(*this); }   // necessary for deep-cloning

        glm::vec3 position    = {0, 0, 0};
        glm::vec3 rotationDeg = {0, 0, 0};
        glm::vec3 scale       = {1, 1, 1};
       
        glm::mat4 GetMatrix();

        glm::vec3 GetRightVector();
        glm::vec3 GetUpVector();
        glm::vec3 GetBackwardVector();
        
    };


}