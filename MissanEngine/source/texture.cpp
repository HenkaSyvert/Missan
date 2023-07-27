#include "pch.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "texture.hpp"

#include <spdlog/spdlog.h>

using namespace Missan;
using namespace std;
using namespace ImGui;

Texture::Texture(const string& fileName, WrapMode wm, FilterMode fm) {

	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(fileName.c_str(), &width, &height, &channels, 4);

	if (!localBuffer) {
		spdlog::error("cannot not open {}", fileName);
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	filterMode(fm);
	wrapMode(wm);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	if (localBuffer) stbi_image_free(localBuffer);


}



Texture::WrapMode Texture::wrapMode() {
	return _wrapMode;
}

void Texture::wrapMode(WrapMode wm) {
	glBindTexture(GL_TEXTURE_2D, id);
	_wrapMode = wm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)wm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)wm);
}


Texture::FilterMode Texture::filterMode() {
	return _filterMode;
}

void Texture::filterMode(FilterMode fm) {
	glBindTexture(GL_TEXTURE_2D, id);
	_filterMode = fm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)fm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)fm);
}

void Texture::DisplayInInspector() {
	unordered_map<WrapMode, string> wmMap;
	wmMap[WrapMode::Repeat] = "repeat";
	wmMap[WrapMode::MirroredRepeat] = "mirrored repeat";
	wmMap[WrapMode::ClampToEdge] = "clamp to edge";
	wmMap[WrapMode::ClampToBorder] = "clamp to border";
	unordered_map<FilterMode, string> fmMap;
	fmMap[FilterMode::Nearest] = "nearest";
	fmMap[FilterMode::Linear] = "linear";
	if (TreeNode("Texture")) {
		if (BeginCombo("Wrap Mode", wmMap[_wrapMode].c_str())) {
			for (auto wm : wmMap)
				if (Selectable(wm.second.c_str(), _wrapMode == wm.first)) wrapMode(wm.first);
			EndCombo();
		}
		if (BeginCombo("Filter Mode", fmMap[_filterMode].c_str())) {
			for (auto fm : fmMap)
				if (Selectable(fm.second.c_str(), _filterMode == fm.first)) filterMode(fm.first);
			EndCombo();
		}
		TreePop();
	}
}