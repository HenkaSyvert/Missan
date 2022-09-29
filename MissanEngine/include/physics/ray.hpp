#pragma once

#include "glm/vec3.hpp"

namespace Missan {

	class Ray {

	public:
		Ray(glm::vec3 orig, glm::vec3 dir) {
			origin = orig;
			direction = dir;
		}

		glm::vec3 origin;
		glm::vec3 direction;


	};

}