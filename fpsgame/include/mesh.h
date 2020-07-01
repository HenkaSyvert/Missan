#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace missan {

    class Mesh {

    private:
        GLuint vaoID = 0;
        int vertexCount = 0;

    public:
        Mesh(GLuint id, int vertexCount);

        GLuint GetVaoID();
        
        int GetVertexCount();

    };

}