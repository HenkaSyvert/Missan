#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace missan;

// PRIVATE
void Camera::UpdateMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, zNear, zFar);
}


// PUBLIC
Camera::Camera(float aspectRatio) {
    this->aspectRatio = aspectRatio;
    UpdateMatrix();
}

Transform& Camera::GetTransform() {
	return transform;
}

void Camera::HandleInput(Input& input, double deltaTime) {
    glm::dvec2 mouseDelta = input.GetMouseDelta();

    glm::vec3 newRot(rotationSpeed * mouseDelta.y, rotationSpeed * mouseDelta.x, 0);

    transform.rotation += newRot;

    int xAxis = 0, zAxis = 0;

    if (input.IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_W)) zAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_S)) zAxis -= 1;

    glm::vec3 deltaPos = (glm::vec3(xAxis,  0,zAxis) * moveSpeed) * transform.rotation;
    transform.position += deltaPos;

}

glm::mat4 Camera::GetProjection() {
    return projectionMatrix;
}

void Camera::SetZNear(float z) {
    zNear = z;
    UpdateMatrix();
}

void Camera::SetZFar(float z) {
    zFar = z;
    UpdateMatrix();
}

void Camera::SetFOV(float fov) {
    fieldOfViewDeg = fov;
    UpdateMatrix();
}

void Camera::SetRotationSpeed(float s) {
    rotationSpeed = s;
}

void Camera::SetMoveSpeed(float s) {
    moveSpeed = s;
}

void Camera::SetAspectRatio(float ar) {
    aspectRatio = ar;
}