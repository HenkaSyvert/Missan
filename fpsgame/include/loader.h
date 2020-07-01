#pragma once

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <vector>
#include <string>

#include "mesh.h"
#include "texture.h"

namespace missan {

    class Loader {
    public:

        Mesh CreateMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<float>& texCoords);
        Mesh CreateCubeMesh(float size = 1);
        Mesh CreatePlaneMesh(float w, float h);

        Texture LoadTexture(std::string filename);

        void FreeAssets();

        static std::string LoadShader(std::string filename);

    private:
        std::vector<GLuint> vaos, vbos, texs;

        static const std::string texturePath, shaderPath;

        GLuint CreateVAO();

        GLuint CreateIndexBuffer(std::vector<unsigned int>& indices);

        GLuint StoreInAttribList(int attribIndex, int elementSize, std::vector<float>& data);

    };

}