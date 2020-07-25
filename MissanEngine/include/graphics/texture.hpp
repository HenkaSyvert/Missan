#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>

namespace missan {

	class Texture {
	public:
		const GLuint textureID = 0;
		const std::string fileName;
		const int width = 0; 
		const int height = 0; 
		const int bitsPerPixel = 0;	// todo: make relevant

		Texture(GLuint newTextureID, const std::string& newFileNameint, int w, int h, int bpp);
		void Bind(int textureSlot = 0);

	};

}