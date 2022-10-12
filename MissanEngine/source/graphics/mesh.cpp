#include "graphics/mesh.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "engine.hpp"

using namespace Missan;
using namespace std;


static GLuint StoreInAttribList(int attribIndex, int elementSize, const vector<float>& data) {
	GLuint vboId;
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, elementSize, GL_FLOAT, GL_FALSE, 0, 0);

	return vboId;
}




void Mesh::Load(const string& fileName) {

	ifstream file(fileName);
	if (!file) {
		cout << "error: unable to open file " << fileName << endl;
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

	IdType id = Object::GetUniqueId();
	resources.Add<Mesh>(id);
	Mesh* m = resources.Get<Mesh>(id);
	m->id = id;

	glGenVertexArrays(1, &m->vaoId);
	glBindVertexArray(m->vaoId);

	GLuint iboId;
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	StoreInAttribList(0, 3, vertices);
	StoreInAttribList(1, 2, uvs);
	StoreInAttribList(2, 3, normals);

	m->elementCount = vertices.size() * 3;
	m->name = fileName;
}
