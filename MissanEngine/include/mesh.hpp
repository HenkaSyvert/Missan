#pragma once

#include <vector>
#include <string>
#include <glm/vec3.hpp>


namespace Missan {

    /// 
    /// Stores data about 3D model
    class Mesh {

    public:
        int vaoId;

        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;

        /// 
        /// Creates new Mesh
        Mesh(int vaoId, const std::vector<float>& vertices, const std::vector<unsigned int>& indices);

    };

}