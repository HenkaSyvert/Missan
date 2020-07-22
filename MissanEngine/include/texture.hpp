#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace missan {

	class Texture {
	private:
		GLuint textureID = 0;
		int width = 0; 
		int height = 0; 
		int bpp = 0;

	public:
		Texture(GLuint id = 0, int w = 0, int h = 0, int bpp = 0);

		int GetWidth();
		int GetHeight();
		int GetBPP();

		void Bind(int textureSlot = 0);

	};

}