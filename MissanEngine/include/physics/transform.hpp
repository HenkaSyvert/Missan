#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "component.hpp"
#include "inspectable.hpp"

#include <iostream>

namespace Missan {

    /// 
    /// Stores position, rotation, and scale of a GameObject
    class Transform : public Component<Transform> {

    public:
        /// 
        /// In world space        
        glm::vec3 position = { 0, 0, 0 };

        /// 
        /// In world space
        glm::vec3 rotation = { 0, 0, 0 };

        /// 
        /// Global scale
        glm::vec3 scale = { 1, 1, 1 };

        /// 
        /// Matrix to transform point from local space to world space
        glm::mat4 matrix = glm::mat4(1.0f);

        glm::mat4 inverseMatrix = glm::mat4(1.0f);

        /// 
        /// Transforms a point from local space to world space
        glm::vec3 TransformPoint(glm::vec3& point);

        /// 
        /// Transforms several points from local space to world space
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points);

        /// 
        /// Local right vector
        glm::vec3 right = { 1, 0, 0 };

        /// 
        /// Local up vector
        glm::vec3 up = { 0, 1, 0 };

        /// 
        /// Local forward vector
        glm::vec3 forward = { 0, 0, 1 };

        void Start();
        void Update();
        void DisplayInInspector();

    };


}

