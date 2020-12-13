#pragma once

#include "core/keycode.hpp"
#include "core/mousebutton.hpp"
#include "core/vector3.hpp"

namespace Missan {

	/// 
	/// Interface to Input system
	namespace Input {

		/// 
		/// Current X and Y of mouse. Note that {0, 0} is in top-left corner
		extern const Vector3& mousePosition;

		/// 
		/// Delta X and Y since last frame. Note that {0, 0} is in top-left corner
		extern const Vector3& mouseDelta;



		///
		/// Returns true the frame the user pressed the key
		bool GetKeyDown(Keycode keycode);

		/// 
		/// Returns true while the users holds down the key
		bool GetKey(Keycode keycode);

		///
		/// Returns true the frame the user releases the key
		bool GetKeyUp(Keycode keycode);



		///
		/// returns true the frame given button is first pressed.
		bool GetMouseButtonDown(MouseButton button);

		///
		/// returns true while the users holds the button
		bool GetMouseButton(MouseButton button);

		///
		/// returns true the frame the user releases the key
		bool GetMouseButtonUp(MouseButton button);
		
	}

}