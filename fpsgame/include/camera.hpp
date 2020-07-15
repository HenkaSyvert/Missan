#pragma once

#include <glm/glm.hpp>

#include "transform.hpp"
#include "window.hpp"

namespace missan {

	class Camera {
	private:
		Window*    window_ptr	 = nullptr;
		Transform* transform_ptr = nullptr;
	
		float fieldOfViewDeg = 45.0f;
		float nearZ			 = 0.1f;
		float farZ			 = 100.0f;
		float aspectRatio;

		glm::mat4 projectionMatrix;

		void UpdateMatrix();

	public:
		Camera(Window& window);

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