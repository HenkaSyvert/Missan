#include "camera.hpp"
#include "window.hpp"

using namespace Missan;

Camera* Camera::main = nullptr;

Camera::Camera() {
	if (!main) main = this;
}

void Camera::UpdateMatrices() {
	if (_projection == Projection::perspective) {
		projectionMatrix = glm::perspective(glm::radians(_fov), _ar, _near, _far);
	}
	else if (_projection == Projection::orthographic) {
		projectionMatrix = glm::ortho(0.0f, _ar * _orthoSize, 0.0f, _orthoSize, _near, _far);
	}
}

