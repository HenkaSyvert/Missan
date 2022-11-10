#pragma once

#include "graphics/color.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "inspectable.hpp"

namespace Missan {

	class Material {

	public:
		glm::vec4 ambient = Color::blue;
		glm::vec4 diffuse = Color::blue;
		glm::vec4 specular = Color::blue;
		float shininess = 32.0f;

		Shader* shader = nullptr;
		Texture* texture = nullptr;

		void DisplayInInspector() {
			using namespace ImGui;
			if (TreeNode("Material")) {
				ColorEdit4("ambient", (float*)&ambient);
				ColorEdit4("diffuse", (float*)&diffuse);
				ColorEdit4("specular", (float*)&specular);
				DragFloat("shininess", &shininess);
				if (texture) texture->DisplayInInspector();
				if (BeginMenu("Shader")) {
					if (MenuItem("Unlit")) shader = Shader::unlit;
					if (MenuItem("Phong")) shader = Shader::phong;
					EndMenu();
				}
				TreePop();
			}
		}
		
	};

}