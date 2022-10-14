#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>

#include <Windows.h>

#include "internal.hpp"
#include "graphics/texture.hpp"
#include "graphics/shader.hpp"
#include "graphics/material.hpp"

#define MISSAN_DEBUG_RESOURCES 0

using namespace Missan;
using namespace std;


static void PrintCurrentDirectory() {
	// print current directory
	DWORD nBufferLength = 0;
	LPSTR lpBuffer = NULL;

	// pass in 0 and NULL to get required length
	nBufferLength = GetCurrentDirectory(nBufferLength, lpBuffer);

	// actually get current dir
	lpBuffer = (LPSTR)alloca(nBufferLength * sizeof(TCHAR));
	GetCurrentDirectory(nBufferLength, lpBuffer);

	cout << "current dir is: " << lpBuffer << endl;


	WIN32_FIND_DATAA findData;
	LPCSTR fileName = "*";
	HANDLE findFile = FindFirstFile(fileName, &findData);

	do {
		cout << "file: " << findData.cFileName << endl;
	} while (FindNextFile(findFile, &findData));

}

void LoadAllFilesInDir(const char* dir, const char* filePattern, void loadFunc(const std::string&) ) {
	SetCurrentDirectory(dir);
	if (MISSAN_DEBUG_RESOURCES) PrintCurrentDirectory();
	WIN32_FIND_DATAA findData;
	HANDLE findFile = FindFirstFile(filePattern, &findData);
	do {
		if (findData.cFileName[0] == '.') continue; //TODO: very elegant solution.. 
		if(MISSAN_DEBUG_RESOURCES)cout << dir << "::Load(" << filePattern << ": " << findData.cFileName << ")\n";
		loadFunc(findData.cFileName);
	} while (FindNextFile(findFile, &findData));
	SetCurrentDirectory("..");
}

void ResourcesInitialize() {

	SetCurrentDirectory("resources");

	LoadAllFilesInDir("meshes", "*.mesh", Mesh::Load);
	LoadAllFilesInDir("textures", "*.png", Texture::Load);
	LoadAllFilesInDir("shaders", "*", Shader::Load);
	LoadAllFilesInDir("materials", "*.mat", Material::Load);

}