#pragma once

#include "missanpch.hpp"

namespace missan {

    // Stores data about 3D model
    class Mesh {

    public:
        
        // Vertices
        const std::vector<float> vertices;

        // Indices for the Vertices
        const std::vector<unsigned int> indices;

        // File name
        const std::string fileName;



        // Creates new Mesh
        Mesh(GLuint newVaoID, 
            const std::string& newFileName,
            const std::vector<float>& newVertices,
            const std::vector<unsigned int> newIndices);



        // NOT PART OF PUBLIC API ///////////////////////////
        const GLuint vaoID = 0;

    };

}