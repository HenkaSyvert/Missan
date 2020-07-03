#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.h"

namespace missan {

	class Input {
	private:
		Window* window_ptr;
		glm::dvec2 mousePos, mouseDelta = glm::dvec2(0, 0);
		double time = 0, deltaTime = 0;

	public:
		Input(Window& window);

		bool IsKeyPressed(int keycode);
		
		glm::dvec2 GetMousePos();
		glm::dvec2 GetMouseDelta();

		double GetTime();
		double GetDeltaTime();

		void Update();


	};

}