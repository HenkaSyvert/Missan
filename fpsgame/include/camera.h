#pragma once

#include <glm/glm.hpp>

#include "transform.h"
#include "input.h"
#include "window.h"

namespace missan {

	class Camera {
	private:
		Window* window_ptr;
		Transform transform;
	
		float fieldOfViewDeg, nearZ, farZ, aspectRatio;

		float moveSpeed, rotationSpeedDeg;

		float pitchConstraint = 89.0f;


		glm::mat4 projectionMatrix;

		void UpdateMatrix();

	public:
		Camera(Window& window);
		void RestoreDefaults();
		Transform& GetTransform();
		void HandleInput(Input& input);

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

		float GetNearZ();
		void SetNearZ(float z);
		
		float GetFarZ();
		void SetFarZ(float z);
		
		float GetFOV();
		void SetFOV(float fov);

		float GetAspectRatio();
		void SetAspectRatio(float ar);

		void SetRotationSpeed(float s);
		void SetMoveSpeed(float s);

	};

}