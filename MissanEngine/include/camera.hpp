#pragma once

#include "component.hpp"
#include "window.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace Missan {

	/// 
	/// Provides view- and projection matrices to transform GameObjects in Scene to screen space
	class Camera : public Component {

	public:

		enum class Projection { orthographic, perspective };

		Camera();

		static Camera* main;

		/// 
		/// The field of view in degrees, i.e. how "wide" the Camera sees around the y-axis
		__declspec(property(get = getFov, put = putFov))float fieldOfView;
		inline float getFov() { return _fov; }
		inline void putFov(float f) { _fov = f; UpdateMatrices(); }

		/// 
		/// Objects closer to the Camera than this will be clipped, i.e. not rendered
		__declspec(property(get = getNear, put = putNear))float nearClipPlane;
		inline float getNear() { return _near; }
		inline void putNear(float n) { _near = n; UpdateMatrices(); }

		/// 
		/// Objects farther away from the Camera than this will be clipped, i.e. not rendered
		__declspec(property(get = getFar, put = putFar))float farClipPlane;
		inline float getFar() { return _far; }
		inline void putFar(float f) { _far = f; UpdateMatrices(); }

		/// 
		/// Screen Width divided by Height, also how "squeezed" the view is on the y-axis
		__declspec(property(get = getAr, put = putAr)) float aspectRatio;
		inline float getAr() { return _ar; }
		inline void putAr(float ar) { _ar = ar; UpdateMatrices(); }

		__declspec(property(get = getOrthoSize, put = putOrthoSize)) float orthographicSize;
		inline float getOrthoSize() { return _orthoSize; }
		inline void putOrthoSize(float os) { _orthoSize = os; UpdateMatrices(); }

		__declspec(property(get = getProj, put = putProj)) Projection projection;
		inline Projection getProj() { return _projection; }
		inline void putProj(Projection p) { _projection = p; UpdateMatrices(); };

		/// 
		/// The projection matrix, which transform points from world space to screen space
		glm::mat4 projectionMatrix = glm::mat4(0);

		glm::vec4 clearColor = { .1,.1,.1,.1 };


		inline void Start() { UpdateMatrices(); }
		Camera* Clone() const { return new Camera(*this); }

	private:
		float _fov = 45;
		float _near = 0.1f;
		float _far = 100;
		float _ar = Window::aspectRatio;
		float _orthoSize = 1;
		Projection _projection = Projection::perspective;


		void UpdateMatrices();
	};
}