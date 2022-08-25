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

		/// 
		/// Does cleanup, frees memory etc.
		void Terminate();
	
	}

}

