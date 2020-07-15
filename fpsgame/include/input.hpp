#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hpp"

namespace missan {

	class Input {
	private:
		Window* window_ptr = nullptr;

		glm::dvec2 mousePos;
		glm::dvec2 mouseDelta = glm::dvec2(0, 0);

		double time		 = 0; 
		double deltaTime = 0;

	public:
		Input(Window& window);
		bool IsKeyPressed(int keycode);
		void Update();

		glm::dvec2 GetMousePos();
		glm::dvec2 GetMouseDelta();

		double GetTime();
		double GetDeltaTime();

		

	};

}