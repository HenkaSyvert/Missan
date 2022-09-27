#pragma once

#include "shaderprogram.hpp"
#include "gameobject.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "texture.hpp"

namespace Missan {

	/// 
	/// Stores data about 3D model
	class Mesh {

	public:
		int vaoId;

		// vertices.size() * 3
		int elementCount;

		/// 
		/// Creates new Mesh
		Mesh(int vaoId, int vertexCount);

	};

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform
	class Renderer : public Component {

	public:

		/// 
		/// Mesh to render
		Mesh* mesh = nullptr;

		/// 
		/// Texture to render
		Texture* texture = nullptr;


		Renderer* Clone() const { return new Renderer(*this); }

	};

	///
	/// Graphics functions
	namespace Graphics {

		extern ShaderProgram* shader;

	}

}