#pragma once

#include <GL/glew.h>
#include <glfw/glfw3.h>

#include <vector>
#include <string>

#include "mesh.hpp"
#include "texture.hpp"

namespace missan {

    class Loader {

    public:
        static std::string LoadShader(std::string filename);

        Mesh CreateMesh(
            const std::vector<float>& vertices, 
            const std::vector<unsigned int>& indices, 
            const std::vector<float>& texCoords);
        Mesh CreateCubeMesh(float size = 1.0f);
        Mesh CreatePlaneMesh(float w = 1.0f, float h = 1.0f);

        Texture LoadTexture(const std::string& filename);
        // WIP
        Texture LoadCubeMapTexture(const std::vector<std::string>& facesFilenames);

        void FreeAssets();

    private:
        std::vector<GLuint> vaos, vbos, texs;
        static const std::string texturePath, shaderPath;     

        GLuint CreateVAO();
        GLuint CreateIndexBuffer(const std::vector<unsigned int>& indices);
        GLuint StoreInAttribList(int attribIndex, int elementSize, const std::vector<float>& data);

    };

}