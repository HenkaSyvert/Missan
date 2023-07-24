#pragma once

#include "ecs.hpp"
#include "inspectable.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace Missan {

    /// 
    /// Stores position, rotation, and scale of a GameObject
    /// Every GameObject has a Transform. Transforms can also have a parent, 
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
        glm::vec3 TransformPoint(glm::vec3& point) {
            glm::vec4 q(point, 1);
            q = localToWorldMatrix * q;
            return glm::vec3(q.x, q.y, q.z);
        }

        /// 
        /// Transforms several points from local space to world space using localToWorldMatrix. 
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points) {
            std::vector<glm::vec3> ps;
            for (auto& p : points)
                ps.push_back(TransformPoint(p));
            return ps;
        }

        void Start() { UpdateMatrix(); }

        void Update() { UpdateMatrix(); }

        void DisplayInInspector() {
            using namespace ImGui;
            if (CollapsingHeader("Transform")) {
                DragFloat3("position", (float*)&position, 0.01f);
                DragFloat3("rotation", (float*)&rotation, 0.1f);
                DragFloat3("scale", (float*)&scale, 0.01f);
            }
        }

    private:

        void UpdateMatrix() {
            using namespace glm;

            // order matters, must be translation-rotation-scale
            localToWorldMatrix = mat4(1.0f);
            localToWorldMatrix = translate(localToWorldMatrix, position);

            // order matters, must be y-z-x
            localToWorldMatrix = rotate(localToWorldMatrix, radians(rotation.y), vec3(0, 1, 0));
            localToWorldMatrix = rotate(localToWorldMatrix, radians(rotation.z), vec3(0, 0, 1));
            localToWorldMatrix = rotate(localToWorldMatrix, radians(rotation.x), vec3(1, 0, 0));

            localToWorldMatrix = glm::scale(localToWorldMatrix, scale);
            worldToLocalMatrix = inverse(localToWorldMatrix);

            right = normalize(localToWorldMatrix[0]);
            up = normalize(localToWorldMatrix[1]);
            forward = -normalize(localToWorldMatrix[2]);

        }

    };

}

