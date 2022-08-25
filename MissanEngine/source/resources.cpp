#include "resources.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <iostream>

#include <stb/stb_image.h>

#include "internal.hpp"

using namespace Missan;
using namespace std;


// All Meshes currently loaded into memory
static vector<Mesh*> loadedMeshes;

// All Textures currently loaded into memory
static vector<Texture*> loadedTextures;

	

// temporary
static vector<GLuint> vaos, vbos, texs;



// Creates a Vertex Array Object
static GLuint CreateVAO() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

// Creates an Index Buffer Object
static GLuint CreateIndexBuffer(const vector<unsigned int>& indices) {
	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	vbos.push_back(iboID);
	return iboID;
}

// Stores data with given elementSize, at given index in attribute list, of currently active VAO
static GLuint StoreInAttribList(int attribIndex, int elementSize, const vector<float>& data) {
	GLuint vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, elementSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return vboID;
}




// Creates new Mesh and stores it on both GPU and in loadedMeshes
static void AddMesh(
	const string& fileName,
	const vector<float>& vertices,
	const vector<unsigned int>& indices,
	const vector<float>& uvs)
{
	GLuint vaoID = CreateVAO();
	GLuint iboID = CreateIndexBuffer(indices);
	GLuint vboID = StoreInAttribList(0, 3, vertices);
	GLuint tex = StoreInAttribList(1, 2, uvs);

	loadedMeshes.push_back(new Mesh(vaoID, fileName, vertices, indices));
}

// Manually creates a cube mesh
static void CreateCubeMesh(float size) {
	float s = size / 2;

	vector<float> vertices = {
		// counter clockwise

		// front
		-s,	-s, -s,		// 0
		-s,  s, -s,		// 1
		s,  s, -s,		// 2
		s, -s, -s,		// 3

		// back
		-s,	-s,  s,		// 4
		-s,  s,  s,		// 5
		s,  s,  s,		// 6
		s, -s,  s,		// 7

		// right
		-s,	-s,  s,		// 8
		-s,  s,  s,		// 9
		-s,  s, -s,		// 10
		-s, -s, -s,		// 11

		// left
		s,	-s,  s,		// 12
		s,  s,  s,		// 13
		s,  s, -s,		// 14
		s, -s, -s,		// 15

		// top
		-s,	-s, -s,		// 16
		-s, -s,  s,		// 17
		s, -s,  s,		// 18
		s, -s, -s,		// 19

		// bottom
		-s,	 s, -s,		// 20
		-s,  s,  s,		// 21
		s,  s,  s,		// 22
		s,  s, -s,		// 23
	};

	vector<unsigned int> indices = {
		// counter clockwise
		0,  1,  3,		 1,  2,  3,	// front
		4,  5,  7,		 5,  6,  7,	// back
		8,  9, 11,		 9, 10, 11,	// right
		12, 13, 15,		13, 14, 15,	// left
		16, 17, 19,		17, 18, 19,	// top
		20, 21, 23,		21, 22, 23	// bottom
	};

	vector<float> uvs = {
		0,0,	0,1,	1,1,		1,0,	// front
		0,0,	0,1,	1,1,		1,0,	// back
		0,0,	0,1,	1,1,		1,0,	// right
		0,0,	0,1,	1,1,		1,0,	// left
		0,0,	0,1,	1,1,		1,0,	// top
		0,0,	0,1,	1,1,		1,0,	// bottom
	};

	AddMesh("unitCube", vertices, indices, uvs);
}

// Manually creates a plane mesh
static void CreatePlaneMesh(float w, float h) {
	w /= 2, h /= 2;
	vector<float> vertices = {
		-w, -h, 0,
		w, -h, 0,
		w,  h, 0,
		-w,  h, 0
	};

	vector<unsigned int> indices = {
		// counter clockwise
		0, 3, 1,	3, 2, 1,
	};

	vector<float> uvs = {
		0,0,
		1,0,
		1,1,
		0,1
	};

	AddMesh("unitPlane", vertices, indices, uvs);
}





// Creates new Texture and stores it both on GPU and in loadedTextures
static void AddTexture(
	const string& fileName,
	unsigned char* data,
	int width,
	int height,
	int numberOfChannels)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
		
	texs.push_back(textureID);
	loadedTextures.push_back(new Texture(textureID, fileName, width, height, numberOfChannels));
}

// Loads Texture data from file and calls AddTexture
static void LoadTexture(const string& fileName) {
	string filePath = Resources::textureDirectory + fileName;
	stbi_set_flip_vertically_on_load(1);
	int w = 0, h = 0, bpp = 0;
	unsigned char* localBuffer = stbi_load(filePath.c_str(), &w, &h, &bpp, 4);

	if (!localBuffer) {
		cout << "Resources error: could not open file \"" << filePath << "\"\n";
		exit(EXIT_FAILURE);
	}
	AddTexture(fileName, localBuffer, w, h, bpp);
	if (localBuffer) stbi_image_free(localBuffer);
}

// work in progress
static Texture LoadCubeMapTexture(const vector<string>& faces) {

	// https://learnopengl.com/Advanced-OpenGL/Cubemaps
	// 
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width = 0, height = 0, nrChannels = 0;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			cout << "Cubemap tex failed to load at path: " << faces[i] << endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return Texture(textureID, "cubemap wip", width, height, nrChannels);
}




string Resources::textureDirectory = "resources/textures/";
string Resources::meshDirectory	= "resources/meshes/";


Mesh* Resources::GetMesh(const string& fileName) {
	for (Mesh* m : loadedMeshes) {
		if (m->fileName.compare(fileName) == 0) {
			return m;
		}
	}
	// TODO: try load mesh file
	return nullptr;
}

Texture* Resources::GetTexture(const string& fileName) {
	for (Texture* t : loadedTextures) {
		if (t->fileName.compare(fileName) == 0) {
			return t;
		}
	}
	LoadTexture(fileName);
	return GetTexture(fileName);
}




void ResourcesInitialize() {
	CreateCubeMesh(1.0f);
	CreatePlaneMesh(1.0f, 1.0f);
}

void ResourcesTerminate() {
	for (Mesh* m : loadedMeshes)   delete m;
	for (Texture* t : loadedTextures) delete t;

	glDeleteVertexArrays(vaos.size(), vaos.data());
	glDeleteBuffers(vbos.size(), vbos.data());
	glDeleteTextures(texs.size(), texs.data());

}


