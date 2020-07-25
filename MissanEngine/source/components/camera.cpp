#include "components/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace missan;

// PUBLIC
void Camera::Restore() {
    fieldOfViewDeg = fovOriginal;
    nearClipPlane = nearzOriginal;
    farClipPlane = farzOriginal;
    aspectRatio = aporiginal;
}

glm::mat4& Camera::GetProjectionMatrix() {
    return projectionMatrix;
}

