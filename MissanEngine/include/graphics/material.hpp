#pragma once

#include "graphics/color.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "inspectable.hpp"

namespace Missan {

	///
	/// A material defines how an object reacts to light. It is possible to have
	/// completely different colors for ambient, diffuse, and specular, but this
	/// would produce unrealistic results, since real physical light is not 
	/// divided this way. 
	class Material {

	public:

		///
		/// The ambient color of this material. This is the color that 
		/// will blend with the lights' ambient colors. 
		glm::vec4 ambient = Color::blue;

		///
		/// The diffuse color of this material. This is the color that 
		/// will blend with the lights' diffuse colors. 
		glm::vec4 diffuse = Color::blue;

		///
		/// The specular color of this material. This is the color that
		/// will blend with the lights' specular colors. 
		glm::vec4 specular = Color::blue;

		///
		/// How shiny this object is. Higher values results in a more concentrated specular
		/// bright spot, giving a more glassy and metallic appearance. 
		float shininess = 32.0f;

		///
		/// The Shader used by the material. 
		Shader* shader = nullptr;

		///
		/// The texture used by this material. 
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