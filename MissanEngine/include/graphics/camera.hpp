#pragma once

#include "ecs.hpp"
#include "graphics/window.hpp"
#include "physics/ray.hpp"
#include "inspectable.hpp"
#include "graphics/color.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace Missan {

	/// 
	/// Camera renders the scene onto to the screen. 
	/// TODO: add camera render to texture. 
	/// Provides projection matrix (and inverse) to transform coordinates from
	/// world space to screen space. 
	/// TODO: Screen space is normalized to... not sure?
	class Camera : public Component<Camera> {

	public:

		/// 
		/// The field of view in degrees, i.e. how "wide" the Camera sees around the y-axis. 
		float fieldOfView = 45;

		/// 
		/// The distance from the Camera (in meters) for which objects closer than this will 
		/// be clipped, i.e. not rendered. 
		float nearClipPlane = 0.1f;

		/// 
		/// The distance from the Camera (in meters) for which objects further away than this will 
		/// be clipped, i.e. not rendered. 
		float farClipPlane = 100;

		/// 
		/// Screen Width divided by Height, also how "squeezed" the view is on the y-axis. 
		float aspectRatio = Window::aspectRatio;

		///
		/// TODO: very this is true: orthographicSize defines half the vertical length of 
		/// the viewing volume. The horizontal length is defined by the aspectRatio. 
		float orthographicSize = 1;


		///
		/// The types of projection supported by the Camera class. Not all fields are used 
		/// by all projections. 
		enum class Projection {

			///
			/// In an orthogonal projection, all projection lines are orthogonal to the
			/// projection plane (thence the name). Orthographic projection uses 
			/// orthographicSize, aspectRatio, and the Camera's Transform. 
			orthographic,

			///
			/// A perspective projection gives the standard 3D effect of objects further
			/// away being smaller. Perspective projection uses fieldOfView, near- and farClipPlane,
			/// aspectRatio, and the Camera's Transform. 
			perspective
		};

		///
		/// The type of projection currently used by the Camera. 
		Projection projection = Projection::perspective;

		/// 
		/// The projection matrix, which transform points from world space to screen space,
		/// as per the type of projection being used. 
		glm::mat4 projectionMatrix;

		///
		/// The color of the background, where no objects have been rendered. 
		glm::vec4 backgroundColor = Color::grey * 0.4f;

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

				ColorEdit4("Background color", (float*)&backgroundColor);
			}
		}

		void Update() {
			if (projection == Projection::perspective) {
				projectionMatrix = glm::perspective(glm::radians(fieldOfView), aspectRatio, nearClipPlane, farClipPlane);
			}
			else if (projection == Projection::orthographic) {
				projectionMatrix = glm::ortho(0.0f, aspectRatio * orthographicSize, 0.0f, orthographicSize, nearClipPlane, farClipPlane);
			}
		}

	};

}
