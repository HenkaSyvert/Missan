#include "loader.hpp"

#include <stb/stb_image.h>

#include <iostream>
#include <fstream>

using namespace missan;


// PUBLIC
std::string Loader::LoadShader(std::string filename) {
	
	std::string path = shaderPath + filename;
	std::fstream input(path);

	if (!input.is_open()) {
		std::cout << "error: could not open \"" << path << "\"\n";
		exit(EXIT_FAILURE);
	}

	std::string str;
	while (input.peek() != EOF)
		str += input.get();

	return str;
}



Mesh Loader::CreateMesh(
	const std::vector<float>& vertices, 
	const std::vector<unsigned int>& indices, 
	const std::vector<float>& texCoords) 
{
    GLuint vaoID = CreateVAO();
    GLuint iboID = CreateIndexBuffer(indices);
	GLuint vboID = StoreInAttribList(0, 3, vertices);
	GLuint tex = StoreInAttribList(1, 2, texCoords);
    return Mesh(vaoID, indices.size());
}

Mesh Loader::CreateCubeMesh(float size) {
	size /= 2;
	std::vector<float> vertices = {
		-size, -size, -size,
		 size, -size, -size,
		 size,  size, -size,
		-size,  size, -size,
		-size, -size,  size,
		 size, -size,  size,
		 size,  size,  size,
		-size,  size,  size
	};

	std::vector<unsigned int> indices = {
		// counter clockwise
		0, 3, 1,	3, 2, 1,	// front
		6, 7, 5,	7, 4, 5,	// back

		1, 2, 5,	2, 6, 5,	// right
		3, 0, 4,	4, 7, 3,	// left

		0, 1, 4,	1, 5, 4,	// top
		2, 3, 7,	7, 6, 2		// bottom	
	};

	std::vector<float> texCoord = {
		// these are wrong
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0,
		0,0,
		0,1,
		1,1,
		1,0
	};

	return CreateMesh(vertices, indices, texCoord);
}

Mesh Loader::CreatePlaneMesh(float w, float h) {
	w /= 2, h /= 2;
	std::vector<float> vertices = {
		-w, -h, 0,
		 w, -h, 0,
		 w,  h, 0,
		-w,  h, 0
	};

	std::vector<unsigned int> indices = {
		// counter clockwise
		0, 3, 1,	3, 2, 1,
	};

	std::vector<float> texCoord = {
		0,0,
		1,0,
		1,1,
		0,1
	};

	return CreateMesh(vertices, indices, texCoord);
}



Texture Loader::LoadTexture(const std::string& filename) {

	std::string path = texturePath + filename;

	stbi_set_flip_vertically_on_load(1);
	int w, h, bpp;
	unsigned char* localBuffer = stbi_load(path.c_str(), &w, &h, &bpp, 4);

	if (!localBuffer) {
		std::cout << "could not open file:" << filename;
		exit(EXIT_FAILURE);
	}

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if(localBuffer) stbi_image_free(localBuffer);
	texs.push_back(textureID);

	return Texture(textureID, w, h, bpp);
}

Texture Loader::LoadCubeMapTexture(const std::vector<std::string>& faces) {
	
	// https://learnopengl.com/Advanced-OpenGL/Cubemaps
	// 
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
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
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return Texture(textureID, width, height, nrChannels);
}



void Loader::FreeAssets() {
	glDeleteVertexArrays(vaos.size(), vaos.data());
	glDeleteBuffers(vbos.size(), vbos.data());
	glDeleteTextures(texs.size(), texs.data());
}



// PRIVATE
const std::string Loader::texturePath = "resources/textures/";
const std::string Loader::shaderPath  = "resources/shaders/";

GLuint Loader::CreateVAO() {
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	vaos.push_back(vaoID);
	return vaoID;
}

GLuint Loader::CreateIndexBuffer(const std::vector<unsigned int>& indices) {
	GLuint iboID;
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
	vbos.push_back(iboID);
	return iboID;
}

GLuint Loader::StoreInAttribList(int attribIndex, int elementSize, const std::vector<float>& data) {
	GLuint vboID;
	vbos.push_back(vboID);
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(attribIndex, elementSize, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return vboID;
}








