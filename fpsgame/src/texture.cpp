#include "texture.hpp"

using namespace missan;

// PUBLIC
Texture::Texture(GLuint id, int w, int h, int bpp) {
	textureID = id;
	width = w;
	height = h;
	this->bpp = bpp;
}

int Texture::GetWidth() {
	return width;
}

int Texture::GetHeight() {
	return height;
}

int Texture::GetBPP() {
	return bpp;
}

void Texture::Bind(int textureSlot) {
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, textureID);
}