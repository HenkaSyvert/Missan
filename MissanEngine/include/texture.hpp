#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Missan {

	/// 
	/// 2D Texture
	class Texture {
	public:

		GLuint textureId = 0;

		/// 
		/// Creates new Texture
		Texture(GLuint id) { textureId = id; }

	};

}