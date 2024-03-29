#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Missan {

	/// 
	/// The Window used by the program
	namespace Window {
		
		/// 
		/// In pixels
		extern const int& width;

		/// 
		/// In pixels
		extern const int& height;

		/// 
		/// Width divided by height
		extern const float& aspectRatio;

		/// 
		/// Set the cursor visible or not
		void SetIsCursorVisible(bool isVisible);
		
	};

}