#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace missan;

// PRIVATE
void Camera::UpdateMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearZ, farZ);
}



// PUBLIC
Camera::Camera() {
    aspectRatio = Window::aspectRatio;
    UpdateMatrix();
}

void Camera::BindToTransform(Transform& transform) {
    transform_ptr = &transform;
}



glm::mat4 Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
    Transform transform;
    if (transform_ptr != nullptr) transform = *transform_ptr;
    return glm::inverse(transform.GetMatrix());
}



float Camera::GetNearZ() {
    return nearZ;
}

void Camera::SetNearZ(float z) {
    nearZ = z;
    UpdateMatrix();
}



float Camera::GetFarZ() {
    return farZ;
}

void Camera::SetFarZ(float z) {
    farZ = z;
    UpdateMatrix();
}



float Camera::GetFOV() {
    return fieldOfViewDeg;
}

void Camera::SetFOV(float fov) {
    fieldOfViewDeg = fov;
    UpdateMatrix();
}



float Camera::GetAspectRatio() {
    return aspectRatio;
}

void Camera::SetAspectRatio(float ar) {
    aspectRatio = ar;
    UpdateMatrix();
}
