#pragma once

#include "scene.hpp"
#include "gameobject.hpp"

namespace missan {

	// The core module
	namespace Engine {

		// Does all required start up stuff
		void Initialize();

		// Actually run the game
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

