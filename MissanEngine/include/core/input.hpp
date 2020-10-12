#pragma once

#include "missanpch.hpp"

namespace Missan {

	/// 
	/// Interface to Input system
	namespace Input {

		/// 
		/// Current X and Y of mouse. Note that {0, 0} is in top-left corner
		extern const glm::dvec2& mousePosition;

		/// 
		/// Delta X and Y since last frame. Note that {0, 0} is in top-left corner
		extern const glm::dvec2& mouseDelta;

		/// 
		/// Is the key pressed?
		bool IsKeyPressed(int keycode);

		///
		/// Is left mouse button pressed?
		bool IsMouseLeftPressed();

		///
		/// Is right mouse button pressed?
		bool IsMouseRightPressed();



		
		// NOT PART OF PUBLIC API //////////////////////
		void Initialize();
		void Update();
		
	}

}