#pragma once

#include "component.hpp"
#include "graphics/color.hpp"

namespace Missan {

	class Light : public Component {

	public:

		static Light* light;

		glm::vec4 ambient = Color::white * .2f;
		glm::vec4 diffuse = Color::white * .5f;
		glm::vec4 specular = Color::white;

		void DisplayInInspector();

		Light* Clone() const { return new Light(*this); }
	};

}