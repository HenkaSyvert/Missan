#pragma once

#include <glm/glm.hpp>

#include "transform.h"
#include "input.h"

namespace missan {

	class Camera {
	private:

		Transform transform;
	
		float fieldOfViewDeg = 45.0f;
		float zNear = 0.1f;
		float zFar = 100.0f;
		float aspectRatio;

		float moveSpeed = 5.0f;
		float rotationSpeedDeg = 30.0f;

		float pitch = 0, yaw = 0;
		float pitchConstraint = 89.0f;


		glm::mat4 projectionMatrix;

		void UpdateMatrix();

	public:
		Camera(float aspectRatio);

		Transform& GetTransform();

		void HandleInput(Input& input);

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		void SetZNear(float z);
		void SetZFar(float z);
		void SetFOV(float fov);
		void SetAspectRatio(float ar);

		// fps cam stuff
		void SetRotationSpeed(float s);
		void SetMoveSpeed(float s);
		//void SetPitch(float pitch);

	};

}