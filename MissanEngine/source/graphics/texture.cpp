#include "graphics/texture.hpp"

#include <stb/stb_image.h>
#include "imgui/imgui.h"
#include "ecs/database.hpp"
#include "engine.hpp"

#include <iostream>
#include <unordered_map>

using namespace Missan;
using namespace std;
using namespace ImGui;

void Texture::Load(const string& fileName, WrapMode wm, FilterMode fm) {

	IdType id = Object::GetUniqueId();
	ECS::Add<Texture>(id);
	Texture* t = ECS::Get<Texture>(id);
	t->id = id;

	stbi_set_flip_vertically_on_load(1);
	unsigned char* localBuffer = stbi_load(fileName.c_str(), &t->_width, &t->_height, &t->_channels, 4);

	if (!localBuffer) {
		cout << "Resources error: could not open file \"" << fileName << "\"\n";
	}

	glGenTextures(1, &t->_textureId);
	glBindTexture(GL_TEXTURE_2D, t->_textureId);

	t->filterMode(fm);
	t->wrapMode(wm);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, t->width, t->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);

	if (localBuffer) stbi_image_free(localBuffer);
	cout << "id: " << id << ", &t: " << t << ", &t->name: " << &t->name << endl;
	//t->name = fileName;


}



Texture::WrapMode Texture::wrapMode() {
	return _wrapMode;
}

void Texture::wrapMode(WrapMode wm) {
	glBindTexture(GL_TEXTURE_2D, _textureId);
	_wrapMode = wm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)wm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)wm);
}


Texture::FilterMode Texture::filterMode() {
	return _filterMode;
}

void Texture::filterMode(FilterMode fm) {
	glBindTexture(GL_TEXTURE_2D, _textureId);
	_filterMode = fm;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)fm);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)fm);
}

void Texture::DisplayInInspector() {
	unordered_map<WrapMode, string> wmMap;
	wmMap[WrapMode::repeat] = "repeat";
	wmMap[WrapMode::mirroredRepeat] = "mirrored repeat";
	wmMap[WrapMode::clampToEdge] = "clamp to edge";
	wmMap[WrapMode::clampToBorder] = "clamp to border";
	unordered_map<FilterMode, string> fmMap;
	fmMap[FilterMode::nearest] = "nearest";
	fmMap[FilterMode::linear] = "linear";
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