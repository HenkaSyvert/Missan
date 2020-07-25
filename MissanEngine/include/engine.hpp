#pragma once

#include "scene.hpp"

namespace missan {

	namespace Engine {

		void Initialize();
		void Run();
		void Terminate();

		void SetActiveScene(Scene& scene);
	}

}

