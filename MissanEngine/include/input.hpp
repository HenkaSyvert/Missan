#pragma once

#include <glm/glm.hpp>

#include "window.hpp"

namespace missan {

	namespace Input {

		extern const glm::dvec2& mousePosition;
		extern const glm::dvec2& mouseDelta;
		bool IsKeyPressed(int keycode);

		// not part of public API
		void Initialize(Window& windowHandle);
		void Update();
		
	}

}