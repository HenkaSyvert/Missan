#pragma once

#include "ecs/component.hpp"
#include "graphics/color.hpp"

namespace Missan {

	class Light : public Component {

	public:


		glm::vec4 ambient = Color::white * .2f;
		glm::vec4 diffuse = Color::white * .5f;
		glm::vec4 specular = Color::white;

		void DisplayInInspector();

	};

}