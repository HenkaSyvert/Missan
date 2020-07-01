#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace missan;

// PRIVATE
void Camera::UpdateMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, zNear, zFar);
}


// PUBLIC
Camera::Camera(float aspectRatio) {
    SetAspectRatio(aspectRatio);
}

Transform& Camera::GetTransform() {
	return transform;
}

void Camera::HandleInput(Input& input) {

    glm::dvec2 mouseDelta = input.GetMouseDelta();
    float deltaTime = (float)input.GetDeltaTime();
    glm::vec3 deltaRotation = rotationSpeedDeg * deltaTime * glm::vec3(mouseDelta.y, mouseDelta.x, 0);
    transform.rotationDeg += deltaRotation;

    int xAxis = 0, zAxis = 0;
    if (input.IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_W)) zAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_S)) zAxis += 1;

    transform.position += (float)xAxis * moveSpeed * deltaTime * transform.GetRightVector();
    transform.position += (float)zAxis * moveSpeed * deltaTime * transform.GetBackwardVector();

}

glm::mat4 Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
    //return glm::lookAt(transform.position, transform.position - transform.GetBackwardVector(), transform.GetUpVector());
    
    return glm::inverse(transform.GetMatrix());
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
    rotationSpeedDeg = s;
}

void Camera::SetMoveSpeed(float s) {
    moveSpeed = s;
}

void Camera::SetAspectRatio(float ar) {
    aspectRatio = ar;
    UpdateMatrix();
}