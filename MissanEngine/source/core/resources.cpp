#include "core/resources.hpp"

#include <GL/glew.h>
#include <glfw/glfw3.h>
#include <stb/stb_image.h>

#include <iostream>
#include <fstream>
#include <vector>

using namespace missan;

// PRIVATE
namespace {

	std::vector<Mesh*>	loadedMeshes;
	std::vector<Texture*> loadedTextures;

	std::vector<GLuint> vaos, vbos, texs;
	const std::string textureDirectory = "resources/textures/";



	// FUNCTIONS
	// OpenGL Loading functions
	GLuint CreateVAO() {
		GLuint vaoID;
		glGenVertexArrays(1, &vaoID);
		glBindVertexArray(vaoID);
		vaos.push_back(vaoID);
		return vaoID;
	}

	GLuint CreateIndexBuffer(const std::vector<unsigned int>& indices) {
		GLuint iboID;
		glGenBuffers(1, &iboID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
		vbos.push_back(iboID);
		return iboID;
	}

	GLuint StoreInAttribList(int attribIndex, int elementSize, const std::vector<float>& data) {
		GLuint vboID;
		vbos.push_back(vboID);
		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(attribIndex, elementSize, GL_FLOAT, GL_FALSE, 0, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vboID;
	}



	// MESHES
	void AddMesh(
		const std::string& fileName,
		const std::vector<float>& vertices,
		const std::vector<unsigned int>& indices,
		const std::vector<float>& texCoords)
	{
		GLuint vaoID = CreateVAO();
		GLuint iboID = CreateIndexBuffer(indices);
		GLuint vboID = StoreInAttribList(0, 3, vertices);
		GLuint tex = StoreInAttribList(1, 2, texCoords);

		loadedMeshes.push_back(new Mesh(vaoID, fileName, vertices, indices));
	}

	void LoadCubeMesh(float size) {
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

		AddMesh("unitCube", vertices, indices, texCoord);
	}

	void LoadPlaneMesh(float w, float h) {
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

		AddMesh("unitPlane", vertices, indices, texCoord);
	}



	// TEXTURES
	void LoadTexture(const std::string& fileName) {

		std::string filePath = textureDirectory + fileName;

		stbi_set_flip_vertically_on_load(1);
		int w = 0, h = 0, bpp = 0;
		unsigned char* localBuffer = stbi_load(filePath.c_str(), &w, &h, &bpp, 4);

		if (!localBuffer) {
			std::cout << "Resources error: could not open file \"" << filePath << "\"\n";
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

		if (localBuffer) stbi_image_free(localBuffer);
		texs.push_back(textureID);
		loadedTextures.push_back(new Texture(textureID, fileName, w, h, bpp));
	}

	Texture LoadCubeMapTexture(const std::vector<std::string>& faces) {

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
				std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
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


}



// PUBLIC
void Resources::Initialize() {
		LoadCubeMesh(1.0f);
		LoadPlaneMesh(1.0f, 1.0f);
	}

void Resources::Terminate() {
		for (Mesh*    m : loadedMeshes)   delete m;
		for (Texture* t : loadedTextures) delete t;

		glDeleteVertexArrays(vaos.size(), vaos.data());
		glDeleteBuffers     (vbos.size(), vbos.data());
		glDeleteTextures    (texs.size(), texs.data());

	}



Mesh* Resources::GetMesh(const std::string& fileName) {

		for (Mesh* m : loadedMeshes) {
			if (m->fileName.compare(fileName) == 0) {
				return m;
			}
		}
		// TODO: try load mesh file
		return nullptr;

	}

Texture* Resources::GetTexture(const std::string& fileName) {
		for (Texture* t : loadedTextures) {
			if (t->fileName.compare(fileName) == 0) {
				return t;
			}
		}
		LoadTexture(fileName);
		return GetTexture(fileName);

	}














