#pragma once

#include "core/gameobject.hpp"

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
		
		/// 
		/// Instantiates a copy of original in the active Scene, and returns pointer to the copy
		GameObject* Instantiate(GameObject& original);

		///
		/// Destroys gameObject
		void Destroy(GameObject* gameObject);
	
	}

}

