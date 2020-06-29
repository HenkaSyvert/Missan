#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace missan {

	class Input {
	private:
		GLFWwindow* window;
		glm::dvec2 mousePos;

	public:
		Input(GLFWwindow* window);

		bool IsKeyPressed(int keycode);
		glm::dvec2 GetMousePos();
		glm::dvec2 GetMouseDelta();




	};

}