#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "component.hpp"

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
        glm::mat4 matrix;

        /// 
        /// Transforms a point from local space to world space
        glm::vec3 TransformPoint(glm::vec3& point);

        /// 
        /// Transforms several points from local space to world space
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points);

        /// 
        /// Local right vector
        glm::vec3 right;

        /// 
        /// Local up vector
        glm::vec3 up;

        /// 
        /// Local forward vector
        glm::vec3 forward;


        void Update();


        Transform* Clone() const { return new Transform(*this); }
        
    };


}

