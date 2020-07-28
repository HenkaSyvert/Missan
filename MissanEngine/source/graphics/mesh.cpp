#include "graphics/mesh.hpp"

using namespace missan;

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
    for (int i = 0; i < vertices.size(); i += 3) {
        verticesVec3_.push_back(glm::vec3(vertices[i], vertices[i + 1], vertices[i + 2]));
    }

    // Get edges
    for (int i = 0; i < indices.size(); i += 3) {
        glm::vec3 a = verticesVec3_[indices[i]];
        glm::vec3 b = verticesVec3_[indices[i + 1]];
        glm::vec3 c = verticesVec3_[indices[i + 2]];
        edges_.push_back({ a, b });
        edges_.push_back({ b, c });
        edges_.push_back({ c, a });
    }

    // Calculate edge directional vectors
    for (auto e : edges_) {
        edgeDirections_.push_back(e.second - e.first);
    }

    // Calculate normals
    for (int i = 0; i < edgeDirections_.size(); i += 3) {
        glm::vec3 a = edgeDirections_[i];
        glm::vec3 b = edgeDirections_[i + 1];
        normals_.push_back(glm::cross(a, b));
    }
	
}

std::vector<glm::vec3> Mesh::GetVerticesVec3() {
    return verticesVec3_;
}

std::vector<std::pair<glm::vec3, glm::vec3>> Mesh::GetEdges() {
    return edges_;
}

std::vector<glm::vec3> Mesh::GetEdgeDirections() {
    return edgeDirections_;
}

std::vector<glm::vec3> Mesh::GetNormals() {
    return normals_;
}

