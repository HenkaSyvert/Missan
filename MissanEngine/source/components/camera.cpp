#include "components/camera.hpp"

using namespace missan;



// PUBLIC

void Camera::Restore() {
    fieldOfViewDeg = fovOriginal_;
    nearClipPlane = nearzOriginal_;
    farClipPlane = farzOriginal_;
    aspectRatio = apOriginal_;
}

glm::mat4& Camera::GetProjectionMatrix() {
    return projectionMatrix_;
}



// PRIVATE

void Camera::Start() {
	fovOriginal_ = fieldOfViewDeg;
	nearzOriginal_ = nearClipPlane;
	farzOriginal_ = farClipPlane;
	apOriginal_ = aspectRatio;
	UpdateMatrix();
}

void Camera::Update() {
	UpdateMatrix();
}

void Camera::UpdateMatrix() {
	projectionMatrix_ = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearClipPlane, farClipPlane);
}