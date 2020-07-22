#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace missan {

	class Window {
	private:
		int width  = 0;
		int height = 0;
		std::string title = "";
		GLFWwindow* windowHandle;

	public:
		Window(int w, int h, std::string name = "Window Title");

		GLFWwindow* GetHandle();

		float GetAspectRatio();
		int GetWidth();
		int GetHeight();

		void SetCursorVisible(bool isVisible);

	};

}