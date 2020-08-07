#pragma once

#include "core/gameobject.hpp"
#include "core/scene.hpp"

namespace Missan {

	// The core module
	namespace Engine {

		// Initializes the engine. Must be called before ALL other Missan functions. 
		void Initialize();

		// Runs the engine. Setup up your game world prior to this. 
		void Run();

		// Cleanup
		void Terminate();

		// Gets active Scene
		Scene* GetActiveScene();

		// Sets active Scene
		void SetActiveScene(Scene& scene);
		
		// Instantiates original in active Scene, and returns copy
		GameObject* Instantiate(GameObject& original);

		
	}

}

