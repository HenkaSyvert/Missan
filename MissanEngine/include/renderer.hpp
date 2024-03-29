#pragma once

#include "ecs.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "shader.hpp"

namespace Missan {

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform. 
	class Renderer : public Component<Renderer> {

	public:

		///
		/// Different types of Renderer. 
		enum class RendererType { 
			
			///
			/// Normal Renderer for a 3D object. 
			Mesh
		};

		///
		/// The type of Renderer this is. 
		RendererType type = RendererType::Mesh;

		/// 
		/// Mesh to render. 
		Mesh* mesh = nullptr;

		///
		/// The Material to render. 
		Material* material = nullptr;

		///
		/// Is this Renderer enabled?
		bool isEnabled = true;

		void Start() {
			if (!material) material = Material::defaultMaterial;
		}

		void DisplayInInspector() {
			using namespace ImGui;
			if (CollapsingHeader("Renderer")) {
				Checkbox("Is Enabled", &isEnabled);
				if (material) material->DisplayInInspector();
			}
		}

	};

}