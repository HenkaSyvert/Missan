#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace missan {

	class Window {
	private:
		int width, height;
		std::string title;
		GLFWwindow* window;

	public:
		Window(int w, int h, std::string name);

		GLFWwindow* GetHandle();

		float GetAspectRatio();
		int GetWidth();
		int GetHeight();

	};

}