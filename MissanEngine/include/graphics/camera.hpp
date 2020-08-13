#pragma once

#include "missanpch.hpp"
#include "core/component.hpp"
#include "core/window.hpp"

namespace Missan {

	/// 
/// Provides view- and projection matrices to transform GameObjects in Scene to screen space
	class Camera : public Component {
	
	public:
		
		/// 
/// The field of view in degrees, i.e. how "wide" the Camera sees around the y-axis
		float fieldOfViewDeg = 45.0f;

		/// 
/// Objects closer to the Camera than this will be clipped, i.e. not rendered
		float nearClipPlane	= 0.1f;

		/// 
/// Objects farther away from the Camera than this will be clipped, i.e. not rendered
		float farClipPlane = 100.0f;

		/// 
/// Screen Width divided by Height, also how "squeezed" the view is on the y-axis
		float aspectRatio = Window::aspectRatio;

	

		/// 
/// Restores Camera default settings
		void Restore();

		/// 
/// Returns the projection matrix, which transform points from world space to screen space
		glm::mat4& GetProjectionMatrix();




		/// 
/// NOT PART OF PUBLIC API ////////////////////////////////////////////////
		Camera* Clone() const { return new Camera(*this); }

		void Start();

		void Update();



	private:

		glm::mat4 projectionMatrix_;

		float fovOriginal_;
		float nearzOriginal_;
		float farzOriginal_;
		float apOriginal_;

		void UpdateMatrix();

	};

}