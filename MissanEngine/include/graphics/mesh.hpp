#pragma once

#include "missanpch.hpp"

namespace missan {

    // Stores data about 3D model
    class Mesh {

    public:
        
        // File name
        const std::string fileName;

        // Vertices
        const std::vector<float> vertices;

        // Indices for the Vertices
        const std::vector<unsigned int> indices;



        // Returns vertices as vec3
        std::vector<glm::vec3> GetVerticesVec3();

        // Returns normals, 1 for each triangle
        std::vector<glm::vec3>& GetNormals();

        

        // Creates new Mesh
        Mesh(GLuint newVaoID, 
            const std::string& newFileName,
            const std::vector<float>& newVertices,
            const std::vector<unsigned int> newIndices);



        // NOT PART OF PUBLIC API ///////////////////////////
        const GLuint vaoID = 0;

    private:
        std::vector<glm::vec3> normals;

    };

}