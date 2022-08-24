#pragma once

#include <vector>
#include <string>
#include <glm/vec3.hpp>


namespace Missan {

    /// 
    /// Stores data about 3D model
    class Mesh {

    public:
        
        /// 
        /// File name
        const std::string fileName;

        /// 
        /// Vertices
        const std::vector<float> vertices;

        /// 
        /// Indices for the Vertices
        const std::vector<unsigned int> indices;



        

        /// 
        /// Get vertices as vec3s
        std::vector<glm::vec3> GetVerticesVec3();

        /// 
        /// Returns normals for each triangle in Mesh
        std::vector<glm::vec3> GetNormals();

        

        /// 
        /// Creates new Mesh
        Mesh(unsigned int newVaoID, 
            const std::string& newFileName,
            const std::vector<float>& newVertices,
            const std::vector<unsigned int> newIndices);



        const unsigned int vaoID = 0;

    private:
        std::vector<glm::vec3> verticesVec3;
        std::vector<glm::vec3> normals;


    };

}