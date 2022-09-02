#pragma once

#include "shaderprogram.hpp"
#include "gameobject.hpp"
#include "window.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace Missan {

	/// 
	/// Provides view- and projection matrices to transform GameObjects in Scene to screen space
	class Camera : public Component {

	public:

		/// 
		/// The field of view in degrees, i.e. how "wide" the Camera sees around the y-axis
		float fieldOfViewDeg = 45.0f;

		/// 
		/// Objects closer to the Camera than this will be clipped, i.e. not rendered
		float nearClipPlane = 0.1f;

		/// 
		/// Objects farther away from the Camera than this will be clipped, i.e. not rendered
		float farClipPlane = 100.0f;

		/// 
		/// Screen Width divided by Height, also how "squeezed" the view is on the y-axis
		float aspectRatio = Window::aspectRatio;

		/// 
		/// The projection matrix, which transform points from world space to screen space
		glm::mat4 projectionMatrix = glm::mat4(0);

		glm::vec4 clearColor = { .1,.1,.1,.1 };


		void inline Update() { projectionMatrix = glm::perspective(glm::radians(fieldOfViewDeg), aspectRatio, nearClipPlane, farClipPlane); }

		Camera* Clone() const { return new Camera(*this); }

	};

	/// 
	/// Stores data about 3D model
	class Mesh {

	public:
		int vaoId;

		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;

		/// 
		/// Creates new Mesh
		Mesh(int vaoId, const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

	};

	/// 
	/// 2D Texture
	class Texture {
	public:

		GLuint textureId = 0;

		/// 
		/// Creates new Texture
		Texture(GLuint id) { textureId = id; }

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

		extern Camera* camera;
		extern ShaderProgram* shader;

		///
		/// Renders a renderer using its mesh and texture
		void Draw(Renderer* renderer);

	}

}