#pragma once

#include "missanpch.hpp"

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



		// NOT PART OF PUBLIC API //////////////////////////
		void Initialize(int width, int height, const std::string& title);
		GLFWwindow* GetHandle();
		
	};

}