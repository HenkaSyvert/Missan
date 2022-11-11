#pragma once

#include "component.hpp"
#include "graphics/color.hpp"

namespace Missan {

	class Light : public Component<Light> {

	public:

		glm::vec4 ambient = { 0.4f, 0.4f, 0.4f, 1 };
		glm::vec4 diffuse = { 0.5, 0.5, 0.5, 1 };
		glm::vec4 specular = Color::white;

		void DisplayInInspector() {
			using namespace ImGui;
			if (CollapsingHeader("Light")) {
				ColorEdit4("ambient", (float*)&ambient);
				ColorEdit4("diffuse", (float*)&diffuse);
				ColorEdit4("specular", (float*)&specular);
			}
		}
	};

}