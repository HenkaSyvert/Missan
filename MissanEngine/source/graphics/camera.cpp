#include "graphics/camera.hpp"
#include "graphics/window.hpp"
#include "physics/transform.hpp"

using namespace Missan;

Camera* Camera::main = nullptr;

Camera::Camera() {
	if (!main) main = this;
}

void Camera::UpdateMatrices() {
	if (_projection == Projection::perspective) {
		_projMat = glm::perspective(glm::radians(_fov), _ar, _near, _far);
	}
	else if (_projection == Projection::orthographic) {
		_projMat = glm::ortho(0.0f, _ar * _orthoSize, 0.0f, _orthoSize, _near, _far);
	}
	_invProjMat = glm::inverse(_projMat);
}

Ray Camera::ScreenPointToRay(glm::vec2 screenPoint) {

	return Ray(ScreenToWorldPoint(glm::vec3(screenPoint, 0)), gameObject->GetComponent<Transform>()->forward);

}

glm::vec3 Camera::ScreenToWorldPoint(glm::vec3 screenPoint) {
	float x = 2.0f * screenPoint.x / Window::width - 1.0f;
	float y = 1.0f - 2.0f * screenPoint.y / Window::height;
	float z = 2.0f * screenPoint.z - 1.0f;
	float w = 1.0f;

	glm::vec4 pos = glm::vec4(x, y, z, w) * _invProjMat;
	pos.w = 1.0f / pos.w;
	pos.x *= pos.w;
	pos.y *= pos.w;
	pos.z *= pos.w;

	return glm::vec3(pos);
}

