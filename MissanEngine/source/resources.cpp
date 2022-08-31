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

#include <stb/stb_image.h>

#include "internal.hpp"

using namespace Missan;
using namespace std;


static unordered_map<string, Mesh*> meshes;
static unordered_map<string, Texture*> textures;

// Stores data with given elementSize, at given index in attribute list, of currently active VAO
static GLuint StoreInAttribList(int attribIndex, int elementSize, const vector<float>& data) {
	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, elementSize, GL_FLOAT, GL_FALSE, 0, 0);

	return vboId;
}

static bool LoadMesh(string fileName) {

	ifstream file(fileName);
	if (!file) {
		cout << "error: unable to open file " << fileName << endl;
		return false;
	}

	vector<float> vertices, uvs;
	vector<unsigned int> indices;

	string token;
	while (!file.eof()) {
		file >> token;
		if (token[0] == '#' || isspace(token[0])) {
			while (file.get() != '\n');
		}
		else {
			if (token == "v") {
				for (int i = 0; i < 3; i++) {
					float v;
					file >> v;
					vertices.push_back(v);
				}
			}
			else if (token == "vt") {
				for (int i = 0; i < 2; i++) {
					float v;
					file >> v;
					uvs.push_back(v);
				}
			}
			else if (token == "f") {
				for (int i = 0; i < 3; i++) {
					float v;
					file >> v;
					indices.push_back(v);
				}
			}
		}
	}

	GLuint vaoId;
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	GLuint iboId;
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	StoreInAttribList(0, 3, vertices);
	StoreInAttribList(1, 2, uvs);

	meshes[fileName] = new Mesh(vaoId, vertices, indices);
	return true;
}

static bool LoadTexture(const string& fileName) {
	stbi_set_flip_vertically_on_load(1);
	int width = 0;
	int height = 0;
	int channels = 0;
	unsigned char* localBuffer = stbi_load(fileName.c_str(), &width, &height, &channels, 4);

	if (!localBuffer) {
		cout << "Resources error: could not open file \"" << fileName << "\"\n";
		return false;
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	textures[fileName] = new Texture(textureID);
	if (localBuffer) stbi_image_free(localBuffer);

	return true;
}


Mesh* Resources::GetMesh(const string& fileName) {
	if (!meshes[fileName] && !LoadMesh(fileName)) return nullptr;
	else return meshes[fileName];
}

Texture* Resources::GetTexture(const string& fileName) {
	if (!textures[fileName] && !LoadTexture(fileName)) return nullptr;
	else return textures[fileName];
}



