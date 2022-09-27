#pragma once

#include "shader.hpp"
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

	class Material {

	public:
		glm::vec4 color = { 1, 1, 1, 1 };
		Shader* shader = nullptr;
		Texture* texture = nullptr;
	};

	/// 
	/// Renders GameObject with Mesh and Texture using its Transform
	class Renderer : public Component {

	public:

		/// 
		/// Mesh to render
		Mesh* mesh = nullptr;

		Material* material = nullptr;

		void Start() { if (!material->shader)material->shader = Shader::standard; }

		Renderer* Clone() const { return new Renderer(*this); }

	};



}