#pragma once

#include "ecs.hpp"
#include "inspectable.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

namespace Missan {

    /// 
    /// Stores position, rotation, and scale of a GameObject
    /// TODO: every GameObject has a Transform. Transforms can also have a parent, 
    /// which allows you to apply position, rotation, and scale hierarchically. This
    /// hierarchy is visible in the Hierarchy window in the Editor. 
    class Transform : public Component<Transform> {

    public:

        /// 
        /// The world space position of the Transform. 
        glm::vec3 position = { 0, 0, 0 };

        /// 
        /// The world space rotation of the Transform (in degrees). 
        glm::vec3 rotation = { 0, 0, 0 };

        /// 
        /// The global scale of the Transform. 
        glm::vec3 scale = { 1, 1, 1 };

        ///
        /// The local right, up, and forward axes of this Transform. 
        glm::vec3 axes[3] = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        };

        /// 
        /// Local right axis. 
        glm::vec3& right = axes[0];

        /// 
        /// Local up axis. 
        glm::vec3& up = axes[1];

        /// 
        /// Local forward axis. 
        glm::vec3& forward = axes[2];

        /// 
        /// Matrix that transforms points from local space to world space. 
        glm::mat4 localToWorldMatrix = glm::mat4(1.0f);

        ///
        /// Matrix that transforms points from world space to local space. 
        glm::mat4 worldToLocalMatrix = glm::mat4(1.0f);

        /// 
        /// Transforms a point from local space to world space using localToWorldMatrix. 
        glm::vec3 TransformPoint(glm::vec3& point);

        /// 
        /// Transforms several points from local space to world space using localToWorldMatrix. 
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points);

        void Start();

        void Update();

        void DisplayInInspector();

    };

}

