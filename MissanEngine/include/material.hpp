#pragma once

#include "color.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "inspectable.hpp"

namespace Missan {

	///
	/// A Material defines how an object reacts to Lights. It is possible to have
	/// completely different colors for ambient, diffuse, and specular, but this
	/// would produce unrealistic results, since real physical light is not 
	/// divided this way. 
	class Material {

	public:

		///
		/// The ambient Color of this Material. This is the Color that 
		/// will blend with the Lights' ambient Colors. 
		Color ambient = Color::lightGrey;

		///
		/// The diffuse Color of this Material. This is the Color that 
		/// will blend with the Lights' diffuse Colors. 
		Color diffuse = Color::lightGrey;

		///
		/// The specular Color of this Material. This is the Color that
		/// will blend with the Lights' specular Colors. 
		Color specular = Color::lightGrey;

		///
		/// How shiny this Material is. Higher values results in a more concentrated specular
		/// bright spot, giving a more glassy and metallic appearance. 
		float shininess = 8;

		///
		/// The Shader used by the Material. 
		Shader* shader = nullptr;

		///
		/// The Texture used by this Material. 
		Texture* texture = nullptr;

		static Material* defaultMaterial;

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