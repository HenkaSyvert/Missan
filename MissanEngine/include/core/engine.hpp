#pragma once

#include "scene.hpp"

namespace missan {

	// The core module
	namespace Engine {

		// Does all required start up stuff
		void Initialize();

		// Actually run the game
		void Run();

		// Cleanup
		void Terminate();

		// Sets active scene
		void SetActiveScene(Scene& scene);
	}

}

