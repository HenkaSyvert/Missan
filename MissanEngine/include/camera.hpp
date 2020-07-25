#pragma once

#include <glm/glm.hpp>

#include "components/transform.hpp"
#include "window.hpp"

namespace missan {

	class Camera {
	private:
		Transform* transform_ptr = nullptr;
	
		float fieldOfViewDeg = 45.0f;
		float nearClipPlane	 = 0.1f;
		float farClipPlane	 = 100.0f;
		float aspectRatio    = 0;

		glm::mat4 projectionMatrix;

		void UpdateMatrix();

	public:
		Camera();

		void BindToTransform(Transform& transform);

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

	};

}