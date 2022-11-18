#pragma once

#include "ecs.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace Missan {

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform
	class Renderer : public Component<Renderer> {

	public:

		enum class RendererType { Mesh, Line };
		RendererType type = RendererType::Mesh;

		/// 
		/// Mesh to render. 
		Mesh* mesh = nullptr;

		///
		/// The Material used to render. 
		Material* material = nullptr;

		bool isEnabled = true;

		void DisplayInInspector() {
			using namespace ImGui;
			if (CollapsingHeader("Renderer")) {
				Checkbox("Is Enabled", &isEnabled);
				if (material) material->DisplayInInspector();
			}
		}

	};

}