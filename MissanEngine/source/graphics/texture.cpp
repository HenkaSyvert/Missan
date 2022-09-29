#include "graphics/texture.hpp"

#include <stb/stb_image.h>

#include <iostream>

using namespace Missan;
using namespace std;


Texture::Texture(const string& fileName, WrapMode wm, FilterMode fm) {

	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(fileName.c_str(), &_width, &_height, &_channels, 4);

	if (!localBuffer) {
		cout << "Resources error: could not open file \"" << fileName << "\"\n";
	}

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);

	filterMode(fm);
	wrapMode(wm);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	if (localBuffer) stbi_image_free(localBuffer);


}



Texture::WrapMode Texture::wrapMode() {
	return _wrapMode;
}

void Texture::wrapMode(WrapMode wm) {
	glBindTexture(GL_TEXTURE_2D, _id);
	_wrapMode = wm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)wm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)wm);
}


Texture::FilterMode Texture::filterMode() {
	return _filterMode;
}

void Texture::filterMode(FilterMode fm) {
	glBindTexture(GL_TEXTURE_2D, _id);
	_filterMode = fm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)fm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)fm);
}