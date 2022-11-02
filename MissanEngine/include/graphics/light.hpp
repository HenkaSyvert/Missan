#pragma once

#include "component.hpp"
#include "graphics/color.hpp"

namespace Missan {

	class Light : public Component {

	public:

		static Light* light;

		glm::vec4 ambient = { 0.2f, 0.2f, 0.2f, 1 };
		glm::vec4 diffuse = { 0.5, 0.5, 0.5, 1 };
		glm::vec4 specular = Color::white;

		void DisplayInInspector();

		Light* Clone() const { return new Light(*this); }
	};

}