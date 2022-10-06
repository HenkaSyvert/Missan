#pragma once

#include "ecs/component.hpp"
#include "graphics/color.hpp"

namespace Missan {

	class Light : public Component {

	public:


		glm::vec4 ambient = {.2, .2, .2, 1};
		glm::vec4 diffuse = {.5, .5, .5, 1};
		glm::vec4 specular = Color::white;

		void DisplayInInspector();

	};

}