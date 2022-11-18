#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace Missan {

	///
	/// Some predefined colors in RGBA format. Each color component is normalized in range [0, 1]. 
	/// Alpha component defines transparancy, with 1 being opaque and 0 being transparent. 
	namespace Color {

		constexpr glm::vec4 red		= {1.0f, 0.0f, 0.0f, 1.0f};
		constexpr glm::vec4 green	= {0.0f, 1.0f, 0.0f, 1.0f};
		constexpr glm::vec4 blue	= {0.0f, 0.0f, 1.0f, 1.0f};
		constexpr glm::vec4 white	= {1.0f, 1.0f, 1.0f, 1.0f};
		constexpr glm::vec4 black	= {0.0f, 0.0f, 0.0f, 1.0f};
		constexpr glm::vec4 clear	= {0.0f, 0.0f, 0.0f, 0.0f};
		constexpr glm::vec4 cyan	= {0.0f, 1.0f, 1.0f, 1.0f};
		constexpr glm::vec4 magenta = {1.0f, 0.0f, 1.0f, 1.0f};
		constexpr glm::vec4 yellow	= {1.0f, 1.0f, 0.0f, 1.0f};
		constexpr glm::vec4 grey	= {0.5f, 0.5f, 0.5f, 1.0f};

	}

}