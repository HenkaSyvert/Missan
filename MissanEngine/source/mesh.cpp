#include "mesh.hpp"

#include <glm/vec3.hpp>
#include <glm/gtx/projection.hpp>

#include <vector>
#include <string>

using namespace Missan;

// PUBLIC
Mesh::Mesh
(
    unsigned int newVaoID,
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
        verticesVec3.push_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
    }

    // Calculate normals
    for (unsigned int i = 0; i < indices.size(); i += 3){
        normals.push_back(glm::cross(verticesVec3[indices[i]], verticesVec3[indices[i + 1]]));
    }
	
}

std::vector<glm::vec3> Mesh::GetVerticesVec3() {
    return verticesVec3;
}

std::vector<glm::vec3> Mesh::GetNormals() {
    return normals;
}

