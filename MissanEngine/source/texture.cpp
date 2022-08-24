#include "texture.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace Missan;
using namespace std;

Texture::Texture(GLuint newTextureID, const string& newFileName, int w, int h, int bpp)
	: textureID(newTextureID),
	fileName(newFileName),
	width(w),
	height(h),
	bitsPerPixel(bpp)
{

}

void Texture::Bind(int textureSlot) {
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}