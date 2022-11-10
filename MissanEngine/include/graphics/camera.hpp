#pragma once

#include "component.hpp"
#include "graphics/window.hpp"
#include "physics/ray.hpp"
#include "inspectable.hpp"
#include "graphics/color.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace Missan {

	/// 
	/// Provides view- and projection matrices to transform GameObjects in Scene to screen space
	class Camera : public Component<Camera> {

	public:

		enum class Projection { orthographic, perspective };

		/// 
		/// The field of view in degrees, i.e. how "wide" the Camera sees around the y-axis
		float fieldOfView = 45;

		/// 
		/// Objects closer to the Camera than this will be clipped, i.e. not rendered
		float nearClipPlane = 0.1f;

		/// 
		/// Objects farther away from the Camera than this will be clipped, i.e. not rendered
		float farClipPlane = 100;

		/// 
		/// Screen Width divided by Height, also how "squeezed" the view is on the y-axis
		float aspectRatio = Window::aspectRatio;

		float orthographicSize = 1;

		Projection projection = Projection::perspective;

		/// 
		/// The projection matrix, which transform points from world space to screen space
		glm::mat4 projectionMatrix;

		glm::mat4 inverseProjectionMatrix;

		glm::vec4 clearColor = Color::grey * 0.1f;

		void DisplayInInspector() {
			using namespace ImGui;
			ShowDemoWindow();

			if (CollapsingHeader("Camera")) {
				SliderFloat("field of view (deg)", &fieldOfView, -15, 400);
				SliderFloat("near clip plane (m)", &nearClipPlane, -5, 10);
				SliderFloat("far clip plane (m)", &farClipPlane, 10, 100);
				SliderFloat("aspect ratio", &aspectRatio, -1, 5);
				SliderFloat("orthographic size", &orthographicSize, -1, 5);

				if (BeginMenu("Projection")) {
					if (MenuItem("Perspective")) projection = Projection::perspective;
					if (MenuItem("Orthographic")) projection = Projection::orthographic;
					EndMenu();
				}

				ColorEdit4("clear color", (float*)&clearColor);
			}
		}

		void Update() {
			if (projection == Projection::perspective) {
				projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane);
			}
			else if (projection == Projection::orthographic) {
				projectionMatrix = glm::ortho(0.0f, aspectRatio * orthographicSize, 0.0f, orthographicSize, nearClipPlane, farClipPlane);
			}
			inverseProjectionMatrix = glm::inverse(projectionMatrix);
		}

	};

}
