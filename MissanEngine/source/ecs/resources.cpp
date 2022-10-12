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

void ResourcesInitialize() {

	PrintCurrentDirectory();
	SetCurrentDirectory("resources");
	PrintCurrentDirectory();


	WIN32_FIND_DATAA findData;
	HANDLE findFile;

	SetCurrentDirectory("meshes");
	PrintCurrentDirectory();
	findFile = FindFirstFile("*.mesh", &findData);
	do {
		Mesh::Load(findData.cFileName);
	} while (FindNextFile(findFile, &findData));
	SetCurrentDirectory("..");

	SetCurrentDirectory("textures");
	PrintCurrentDirectory();
	findFile = FindFirstFile("*.png", &findData);
	do {
		Texture::Load(findData.cFileName);
	} while (FindNextFile(findFile, &findData));
	SetCurrentDirectory("..");

}