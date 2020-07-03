#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>

using namespace missan;

// PRIVATE
void Camera::UpdateMatrix() {
    projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearZ, farZ);
}


// PUBLIC
Camera::Camera(Window& window) {
    window_ptr = &window;
    RestoreDefaults();
}

Transform& Camera::GetTransform() {
	return transform;
}

void Camera::RestoreDefaults() {
    fieldOfViewDeg = 45.0f;
    nearZ = 0.1f;
    farZ = 100.0f;
    aspectRatio = window_ptr->GetAspectRatio();

    moveSpeed = 5.0f;
    rotationSpeedDeg = 15.0f;
}

void Camera::HandleInput(Input& input) {

    
    glm::dvec2 mouseDelta = input.GetMouseDelta();
    float deltaTime = (float)input.GetDeltaTime();
    
    
    float dyRot = -mouseDelta.x * rotationSpeedDeg * deltaTime;
    float dxRot = -mouseDelta.y * rotationSpeedDeg * deltaTime;

    transform.rotationDeg.y += dyRot;
    transform.rotationDeg.x += dxRot;

    if (transform.rotationDeg.x > pitchConstraint) transform.rotationDeg.x = pitchConstraint;
    else if (transform.rotationDeg.x < -pitchConstraint) transform.rotationDeg.x = -pitchConstraint;

    
    

    int xAxis = 0, zAxis = 0;
    if (input.IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_W)) zAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_S)) zAxis += 1;

    float dx = (float)xAxis * moveSpeed * deltaTime;
    float dz = (float)zAxis * moveSpeed * deltaTime;


    transform.position += dx * transform.GetRightVector();
    transform.position += dz * transform.GetBackwardVector();

}

glm::mat4 Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

glm::mat4 Camera::GetViewMatrix() {
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


void Camera::SetRotationSpeed(float s) {
    rotationSpeedDeg = s;
}

void Camera::SetMoveSpeed(float s) {
    moveSpeed = s;
}