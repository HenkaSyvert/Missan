#pragma once

#include "ecs/component.hpp"
#include "graphics/material.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"


namespace Missan {

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform
	class Renderer : public Component {

	public:

		IdType meshId = NULL;
		IdType materialId = NULL;

		void DisplayInInspector();


	};

}