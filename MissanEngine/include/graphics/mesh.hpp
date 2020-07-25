#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace missan {

    class Mesh {

    public:
        const GLuint vaoID = 0;
        const std::vector<float> vertices;
        const std::vector<unsigned int> indices;
        const std::string fileName;

    public:
        Mesh(GLuint newVaoID, 
            const std::string& newFileName,
            const std::vector<float>& newVertices,
            const std::vector<unsigned int> newIndices);


    };

}