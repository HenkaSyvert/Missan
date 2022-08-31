#pragma once

#include "gameobject.hpp"

namespace Missan {

	/// 
	/// The core module
	namespace Engine {

		/// 
		/// Initializes the engine. Must be called before ALL other Missan functions. 
		void Initialize();

		/// 
		/// Runs the engine. Setup up your Scene prior to calling Run().
		void Run();

	}

	/// 
	/// Interface to Time system
	namespace Time {

		/// 
		/// Time (in seconds) at the beginning of this frame, measured from start of game
		extern const float& time;

		/// 
		/// Time (in seconds) since last frame
		extern const float& deltaTime;

	}

}

