#pragma once

#include <glm/vec3.hpp>

namespace Missan {

	///
	/// These map directly to the physical keyboard. It is just a wrapper
	/// around the GLFW keycodes, which is based on the US layout. 
	/// Most names are self explanatory, but I have added comments for
	/// those which are not, and those which differ on a Swedish layout. 
	enum class Keycode : int {

		///
		/// checks all keys
		Any = 0,

		// Printable keys 

		Space = 32,
		///
		/// Ä on Swedish layout
		Apostrophe = 39,
		Comma = 44,
		///
		/// + on Swedish layout
		Minus = 45,
		Period = 46,
		///
		/// - on Swedish layout
		Slash = 47,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		///
		/// Ö on Swedish layout
		Semicolon = 59,
		///
		/// ´ on Swedish layout
		Equal = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		///
		/// Å on Swedish layout
		LeftBracket = 91,
		///
		/// ' on Swedish layout
		Backslash = 92,
		///
		/// ¨ on Swedish layout
		RightBracket = 93,
		///
		/// § on Swedish layout
		GraveAccent = 96,
		//World1            = 161,	// couldn't find these on my keyboard
		//World2            = 162,	// couldn't find these on my keyboard

		// Function keys

		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		//PrintScreen       = 283,	// OS probably handles it before Missan
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		//F12               = 301,	// OS doesn't like you pressing this one
		//F13               = 302,	// couldn't find these on my keyboard
		//F14               = 303,	// couldn't find these on my keyboard
		//F15               = 304,	// couldn't find these on my keyboard
		//F16               = 305,	// couldn't find these on my keyboard
		//F17               = 306,	// couldn't find these on my keyboard
		//F18               = 307,	// couldn't find these on my keyboard
		//F19               = 308,	// couldn't find these on my keyboard
		//F20               = 309,	// couldn't find these on my keyboard
		//F21               = 310,	// couldn't find these on my keyboard
		//F22               = 311,	// couldn't find these on my keyboard
		//F23               = 312,	// couldn't find these on my keyboard
		//F24               = 313,	// couldn't find these on my keyboard
		//F25               = 314,	// couldn't find these on my keyboard
		Keypad0 = 320,
		Keypad1 = 321,
		Keypad2 = 322,
		Keypad3 = 323,
		Keypad4 = 324,
		Keypad5 = 325,
		Keypad6 = 326,
		Keypad7 = 327,
		Keypad8 = 328,
		Keypad9 = 329,
		KeypadDecimal = 330,
		KeypadDivide = 331,
		KeypadMultiply = 332,
		KeypadSubtract = 333,
		KeypadAdd = 334,
		KeypadEnter = 335,
		//KeypadEqual       = 336,	// couldn't find these on my keyboard
		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	};

	///
	/// Mouse button codes. 
	enum class MouseButton : int {
		Left = 0,
		Right = 1,
		ScrollWheel = 2,
		Button3 = 3,
		Button4 = 4
	};

	/// 
	/// Interface to Input system
	namespace Input {

		/// 
		/// Current X and Y coordinates of mouse. Note that {0, 0} is in top-left corner. 
		extern const glm::vec3& mousePosition;

		/// 
		/// Delta X and Y since last frame. Note that {0, 0} is in top-left corner. 
		extern const glm::vec3& mouseDelta;



		///
		/// Returns true the during the first frame the key was pressed. 
		bool GetKeyDown(Keycode keycode);

		/// 
		/// Returns true all frames the key is pressed. 
		bool GetKey(Keycode keycode);

		///
		/// Returns true the first frame key is no longer pressed. 
		bool GetKeyUp(Keycode keycode);



		///
		/// Returns true the during the first frame the button was pressed. 
		bool GetMouseButtonDown(MouseButton button);

		///
		/// Returns true all frames the button is pressed. 
		bool GetMouseButton(MouseButton button);

		///
		/// Returns true the first frame button is no longer pressed. 
		bool GetMouseButtonUp(MouseButton button);
		
	}

}