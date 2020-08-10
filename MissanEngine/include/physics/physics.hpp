#pragma once

#include "missanpch.hpp"

namespace Missan {

	// Interface to the physics system
	namespace Physics {

		// The acceleration due to gravity
		extern glm::vec3 gravity;



		// NOT PART OF PUBLIC API //////////////
		void Update();

	}
}
