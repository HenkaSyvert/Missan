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

#include "internal.hpp"
#include "graphics/texture.hpp"

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

	vector<float> vertices, uvs, normals;
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
					unsigned int v;
					file >> v;
					indices.push_back(v);
				}
			}
			else if (token == "vn") {
				for (int i = 0; i < 3; i++) {
					float v;
					file >> v;
					normals.push_back(v);
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
	StoreInAttribList(2, 3, normals);

	meshes[fileName] = new Mesh(vaoId, vertices.size() * 3);
	return true;
}

// thanks to http://www.songho.ca/opengl/gl_sphere.html for theory
Mesh Resources::GenerateUvSphere(int stacks, int sectors) {

	std::vector<float> vertices;
	std::vector<float> uvs;
	std::vector<unsigned int> indices;
	// line indices? for rendering just longitudes and latitudes. 

	float M_PI = acosf(-1.0f);
	float stackDeltaAngle = M_PI / stacks;
	float sectorDeltaAngle = 2 * M_PI / sectors;

	// there will actually be (sectors + 1) vertices per stack, 
	// because the first and last have same position but different uvs. 
	// also, the poles will contain several vertices rather than one, 
	// for the same reason. 
	for (int stack = 0; stack <= stacks; stack++) {

		float stackAngle = M_PI / 2 - stack * stackDeltaAngle;
		float z = sinf(stackAngle);
		//std::cout << "stack angle: " << stackAngle<<"\n";
		for (int sector = 0; sector <= sectors; sector++) {

			float sectorAngle = sector * sectorDeltaAngle;

			float x = cosf(stackAngle) * cosf(sectorAngle);
			float y = cosf(stackAngle) * sinf(sectorAngle);

			// normals are same as vertices
			vertices.push_back(x / 2);
			vertices.push_back(y / 2);
			vertices.push_back(z / 2);

			//std::cout << "sector angle: " << sectorAngle << ", ";
			//std::cout << "x:" << x << ", y:" << y << ", z:" << z << "\n";

			// texture uv coordinates, normalized to [0, 1] range
			uvs.push_back((float)sector / sectors);
			uvs.push_back((float)stack / stacks);


			// calculate indices. each sector becomes 2 triangles, 
			// except those at the top and bottom which are 1 triangles
			if (stack == stacks || sector == sectors) continue;
			unsigned int k1 = stack * (stacks + 1) + sector;
			unsigned int k2 = (stack + 1) * (stacks + 1) + sector;
			
			if (k1 != 0) {
				indices.push_back(k1);
				indices.push_back(k2);
				indices.push_back(k1 + 1);
			}

			if (k1 != stacks - 1) {
				indices.push_back(k1 + 1);
				indices.push_back(k2);
				indices.push_back(k2 + 1);
			}

		}
		//std::cout << "\n";
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
	StoreInAttribList(2, 3, vertices);

	//std::cout << "vertices.size = " << vertices.size() << "\nindicies.size() = " << indices.size() << "\n";

	return Mesh(vaoId, vertices.size() * 3);
	
}



Mesh* Resources::GetMesh(const string& fileName) {
	if (!meshes[fileName] && !LoadMesh(fileName)) return nullptr;
	else return meshes[fileName];
}

Texture* Resources::GetTexture(const string& fileName) {
	if (!textures[fileName])
		textures[fileName] = new Texture(fileName);
	return textures[fileName];
}



