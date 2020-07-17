#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace missan {

    class Mesh {

    private:
        GLuint vaoID = 0;
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

    public:
        Mesh(
            GLuint id, 
            const std::vector<float>& vertices,
            const std::vector<unsigned int> indices);

        GLuint GetVaoID();

        // currently these just return copies.
        // runtime modified meshes not supported yet
        std::vector<float> GetVertices();
        std::vector<unsigned int> GetIndices();

    };

}