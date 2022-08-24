#pragma once

#include "gameobject.hpp"

#include <vector>

#include <glm/vec3.hpp>

namespace Missan {

	/// 
	/// Interface to the physics system
	namespace Physics {

		/// 
		/// The acceleration due to gravity
		extern glm::vec3 gravity;




		void Update(std::vector<GameObject*> gos);

	}
}
