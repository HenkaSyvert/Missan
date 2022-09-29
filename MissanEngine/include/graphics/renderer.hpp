#pragma once

#include "component.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"


namespace Missan {

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform
	class Renderer : public Component {

	public:

		/// 
		/// Mesh to render
		Mesh* mesh = nullptr;

		Material* material = nullptr;

		void Start() { if (!material->shader)material->shader = Shader::unlit; }

		Renderer* Clone() const { return new Renderer(*this); }

	};

}