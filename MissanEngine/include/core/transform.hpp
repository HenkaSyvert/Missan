#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "core/component.hpp"

namespace Missan {

    /// 
    /// Stores position, rotation, and scale of a GameObject
    class Transform : public Component{

    public:
        
        /// 
        /// In world space
        glm::vec3 position    = {0, 0, 0};

        /// 
        /// In world space
        glm::vec3 rotationDeg = {0, 0, 0};

        /// 
        /// Global scale
        glm::vec3 scale       = {1, 1, 1};
        


        /// 
        /// Matrix to transform point from local space to world space
        glm::mat4 GetMatrix();

        /// 
        /// Transforms a point from local space to world space
        glm::vec3 TransformPoint(glm::vec3& point);

        /// 
        /// Transforms several points from local space to world space
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points);

        /// 
        /// Local right vector
        glm::vec3 GetRightVector();

        /// 
        /// Local up vector
        glm::vec3 GetUpVector();

        /// 
        /// Local backward vector
        glm::vec3 GetBackwardVector();



        // NOT PART OF PUBLIC API ////////////////////////////////
        Transform* Clone() const { return new Transform(*this); }
        
    };


}

