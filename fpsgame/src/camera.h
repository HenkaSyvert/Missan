#pragma once

#include <glm/glm.hpp>

#include "transform.h"
#include "input.h"

namespace missan {

	class Camera {
	private:

		Transform transform;

		float moveSpeed = 1.0f;
		float rotationSpeed = 0.01f;
		float fieldOfViewDeg = 45.0f;
		float zNear = 0.1f;
		float zFar = 100.0f;
		float aspectRatio;

		glm::mat4 projectionMatrix;

		void UpdateMatrix();

	public:
		Camera(float aspectRatio);

		Transform& GetTransform();

		void HandleInput(Input& input, double deltaTime);

		glm::mat4 GetProjection();

		void SetZNear(float z);
		void SetZFar(float z);
		void SetFOV(float fov);
		void SetRotationSpeed(float s);
		void SetMoveSpeed(float s);
		void SetAspectRatio(float ar);
	};

}