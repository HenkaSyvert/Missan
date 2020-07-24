#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace missan {

	namespace Window {
	
		// todo, add resize and fullscreen
		
		extern const int& width;
		extern const int& height;
		extern const float& aspectRatio;

		void Initialize(int width, int height, const std::string& title);
		void SetIsCursorVisible(bool isVisible);

		// should probably be hidden sometime
		GLFWwindow* GetHandle();
		
	};

}