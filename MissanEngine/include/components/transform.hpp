#pragma once

#include "missanpch.hpp"
#include "components/component.hpp"

namespace missan {

    // Stores position, rotation, and scale of a GameObject
    class Transform : public Component{

    public:
        
        // In world space
        glm::vec3 position    = {0, 0, 0};

        // In world space
        glm::vec3 rotationDeg = {0, 0, 0};

        // Global scale
        glm::vec3 scale       = {1, 1, 1};
       


        // Matrix to transform point from local space to world space
        glm::mat4 GetMatrix();

        // Local right vector
        glm::vec3 GetRightVector();

        // Local up vector
        glm::vec3 GetUpVector();

        // Local backward vector
        glm::vec3 GetBackwardVector();



        // NOT PART OF PUBLIC API ////////////////////////////////
        Transform* Clone() const { return new Transform(*this); }
        
    };


}

