#include "graphics/mesh.hpp"

using namespace Missan;

// PUBLIC
Mesh::Mesh
(
    GLuint newVaoID,
    const std::string& newFileName,
    const std::vector<float>& newVertices,
    const std::vector<unsigned int> newIndices
)
    : vaoID(newVaoID),
    fileName(newFileName),
    vertices(newVertices),
    indices(newIndices)
{
    // Do vertices as vec3
    for (unsigned int i = 0; i < vertices.size(); i += 3) {
        verticesVec3_.push_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
    }

    // Calculate normals
    for (unsigned int i = 0; i < indices.size(); i += 3){
        normals_.push_back(glm::cross(verticesVec3_[indices[i]], verticesVec3_[indices[i + 1]]));
    }
	
}

std::vector<glm::vec3> Mesh::GetVerticesVec3() {
    return verticesVec3_;
}

std::vector<glm::vec3> Mesh::GetNormals() {
    return normals_;
}

