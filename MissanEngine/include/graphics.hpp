#pragma once

#include "shader.hpp"
#include "gameobject.hpp"
#include "window.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "color.hpp"

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
		glm::vec4 ambient = Color::white;
		glm::vec4 diffuse = Color::white;
		glm::vec4 specular = Color::white;
		float shininess = 1.0f;

		Shader* shader = nullptr;
		Texture* texture = nullptr;
	};

	class Light : public Component {

	public:

		static Light* light;

		glm::vec4 ambient = Color::yellow * .2f;
		glm::vec4 diffuse = Color::white * .5f;
		glm::vec4 specular = Color::white;
		Light* Clone() const { return new Light(*this); }
	};

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