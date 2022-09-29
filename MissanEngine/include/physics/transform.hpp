#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>
#include "component.hpp"
#include "inspectable.hpp"

namespace Missan {

    /// 
    /// Stores position, rotation, and scale of a GameObject
    class Transform : public Component {

    public:
        
        /// 
        /// In world space        
        __declspec(property(get = getPos, put = putPos)) glm::vec3 position;
        inline glm::vec3& getPos() {return _position; }
        inline void putPos(glm::vec3 p) { _position = p; UpdateMatrix(); }

        /// 
        /// In world space
        __declspec(property(get = getRot, put = putRot)) glm::vec3 rotation;
        inline glm::vec3& getRot() { return _rotation; }
        inline void putRot(glm::vec3 r) { _rotation = r; UpdateMatrix(); }

        /// 
        /// Global scale
        __declspec(property(get = getScale, put = putScale)) glm::vec3 scale;
        inline glm::vec3& getScale() { return _scale; }
        inline void putScale(glm::vec3 s) { _scale = s; UpdateMatrix(); }

        /// 
        /// Matrix to transform point from local space to world space
        __declspec(property(get = getMatrix)) glm::mat4 matrix;
        inline glm::mat4 getMatrix() { return _matrix; }

        __declspec(property(get = getInvMatrix)) glm::mat4 inverseMatrix;
        inline glm::mat4 getInvMatrix() { return _invMat; }

        /// 
        /// Transforms a point from local space to world space
        glm::vec3 TransformPoint(glm::vec3& point);

        /// 
        /// Transforms several points from local space to world space
        std::vector<glm::vec3> TransformPoints(std::vector<glm::vec3> points);

        /// 
        /// Local right vector
        __declspec(property(get = getRight)) glm::vec3 right;
        inline glm::vec3 getRight(){return normalize(matrix[0]);}

        /// 
        /// Local up vector
        __declspec(property(get = getUp)) glm::vec3 up;
        inline glm::vec3 getUp() { return normalize(matrix[1]); }

        /// 
        /// Local forward vector
        __declspec(property(get = getForward)) glm::vec3 forward;
        inline glm::vec3 getForward() { return -normalize(matrix[2]); }

        void Start() { UpdateMatrix(); }
        void DisplayInInspector();

        Transform* Clone() const { return new Transform(*this); }
        
    private:
        glm::vec3 _position = { 0, 0, 0 };
        glm::vec3 _rotation = { 0, 0, 0 };
        glm::vec3 _scale = { 1, 1, 1 };
        glm::mat4 _matrix;
        glm::mat4 _invMat;

        void UpdateMatrix();

    };


}

