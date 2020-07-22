#include "mesh.hpp"

using namespace missan;

// PUBLIC
Mesh::Mesh(
	GLuint id, 
	const std::vector<float>& verts,
	const std::vector<unsigned int> inds)
{ 
	vaoID = id;
	vertices = verts;
	indices = inds;
}

GLuint Mesh::GetVaoID() {
	return vaoID;
}

std::vector<float> Mesh::GetVertices() {
	return vertices;
}

std::vector<unsigned int> Mesh::GetIndices() {
	return indices;
}
