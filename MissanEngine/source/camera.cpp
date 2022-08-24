#include "camera.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Missan;


void Camera::Restore() {
    fieldOfViewDeg = fovOriginal;
    nearClipPlane = nearzOriginal;
    farClipPlane = farzOriginal;
    aspectRatio = apOriginal;
}

glm::mat4& Camera::GetProjectionMatrix() {
    return projectionMatrix;
}



void Camera::Start() {
	fovOriginal = fieldOfViewDeg;
	nearzOriginal = nearClipPlane;
	farzOriginal = farClipPlane;
	apOriginal = aspectRatio;
	UpdateMatrix();
}

void Camera::Update() {
	UpdateMatrix();
}

void Camera::UpdateMatrix() {
	projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearClipPlane, farClipPlane);
}