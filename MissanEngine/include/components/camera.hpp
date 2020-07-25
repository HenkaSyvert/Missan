#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "components/component.hpp"
#include "core/window.hpp"

namespace missan {

	class Camera : public Component {
	public:
	
		float fieldOfViewDeg = 45.0f;
		float nearClipPlane	 = 0.1f;
		float farClipPlane	 = 100.0f;
		float aspectRatio = Window::aspectRatio;

		

	private:
		glm::mat4 projectionMatrix;

		// for Restore()
		float fovOriginal;
		float nearzOriginal;
		float farzOriginal;
		float aporiginal;

	public:
		Camera* Clone() const { return new Camera(*this); }   // necessary for deep-cloning

		void Restore();

		void Start() {
			// save defaults for Restore()
			fovOriginal = fieldOfViewDeg;
			nearzOriginal = nearClipPlane;
			farzOriginal = farClipPlane;
			aporiginal = aspectRatio;
		}

		void Update() {
			projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearClipPlane, farClipPlane);
		}

		glm::mat4& GetProjectionMatrix();


	};

}