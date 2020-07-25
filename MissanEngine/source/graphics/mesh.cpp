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
	
	// using inefficient method which gets 
	// normals from each triangle. 

	for (int i = 0; i < indices.size(); i += 3) {
		float x1 = vertices[indices[i]];
		float y1 = vertices[indices[i] + 1];
		float z1 = vertices[indices[i] + 2];

		float x2 = vertices[indices[i + 1]];
		float y2 = vertices[indices[i + 1] + 1];
		float z2 = vertices[indices[i + 1] + 2];

		float x3 = vertices[indices[i + 2]];
		float y3 = vertices[indices[i + 2] + 1];
		float z3 = vertices[indices[i + 2] + 2];

		glm::vec3 a(x1, y1, z1);
		glm::vec3 b(x2, y2, z2);
		glm::vec3 c(x3, y3, z3);

		glm::vec3 ab(a + b);
		glm::vec3 ac(a + c);
		normals.push_back(glm::cross(ab, ac));
	}
	
}

std::vector<glm::vec3> Mesh::GetVerticesVec3() {
	std::vector<glm::vec3> v;
	for (int i = 0; i < vertices.size(); i += 3)
		v.push_back({ vertices[0], vertices[1], vertices[2] });
	return v;
}

std::vector<glm::vec3>& Mesh::GetNormals() {
    return normals;
}