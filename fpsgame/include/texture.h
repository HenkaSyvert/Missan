#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace missan {

	class Texture {
	private:
		GLuint textureID;
		int width, height, bpp;

	public:
		Texture(GLuint id, int w, int h, int bpp);

		GLuint GetID();
		int GetWidth();
		int GetHeight();
		int GetBPP();

	};

}