#include "camera.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Missan;
using namespace glm;

void Camera::Update() {
	projectionMatrix = perspective(radians(fieldOfViewDeg), aspectRatio, nearClipPlane, farClipPlane);
}
