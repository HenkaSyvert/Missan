#pragma once

#include "ecs.hpp"
#include "graphics/window.hpp"
#include "graphics/color.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace Missan {

	/// 
	/// Camera renders the Scene onto to the screen. 
	class Camera : public Component<Camera> {

	public:

		/// 
		/// The field of view (in degrees), i.e. how "wide" the Camera sees around the y-axis. 
		float fieldOfView = 45;

		/// 
		/// Distance from the Camera (in meters) to the near clip plane. Objects
		/// closer than this will be clipped, i.e. not rendered. 
		float nearClipPlane = 0.1f;

		/// 
		/// Distance from the Camera (in meters) to the far clip plane. Objects
		/// further away than this will be clipped, i.e. not rendered. 
		float farClipPlane = 100;

		/// 
		/// Screen Width divided by Height, how "squeezed" the view is on the y-axis. 
		float aspectRatio = Window::aspectRatio;

		///
		/// The viewing volume, when using Orthographic Projection. The horizontal length 
		/// is defined by the aspectRatio, and vertical length is implicitly defined. 
		float orthographicSize = 1;

		///
		/// The types of Projection supported by the Camera class. Not all fields are used 
		/// by all Projections. 
		enum class Projection {

			///
			/// In an Orthographic Projection, all projection lines are orthogonal to the
			/// projection plane (thence the name). Orthographic Projection uses 
			/// orthographicSize, aspectRatio, and the Camera's Transform. 
			Orthographic,

			///
			/// A Perspective Projection gives the standard 3D effect of objects further
			/// away appearing smaller. Perspective Projection uses fieldOfView, nearClipPlane,
			/// and farClipPlane, aspectRatio, and the Camera's Transform. 
			Perspective
		};

		///
		/// The type of Projection currently used by the Camera. 
		Projection projection = Projection::Perspective;

		/// 
		/// The projection matrix, which transform points from world space to screen space,
		/// as per the type of Projection being used. 
		glm::mat4 projectionMatrix;

		///
		/// The Color of the background, where no objects have been rendered. 
		Color backgroundColor = Color::Lerp(Color::black, Color::white, 0.2);

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
					if (MenuItem("Perspective")) projection = Projection::Perspective;
					if (MenuItem("Orthographic")) projection = Projection::Orthographic;
					EndMenu();
				}

				ColorEdit4("Background color", (float*)&backgroundColor);
			}
		}

		void Update() {
			projectionMatrix = projection == Projection::Perspective
				? glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane)
				: glm::ortho(0.0f, aspectRatio * orthographicSize, 0.0f, orthographicSize, nearClipPlane, farClipPlane);			
		}

	};

}
