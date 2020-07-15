#include "mesh.hpp"

using namespace missan;

// PUBLIC
Mesh::Mesh(GLuint id, int count) { 
	vaoID = id;
	vertexCount = count;
}

GLuint Mesh::GetVaoID() {
	return vaoID;
}

int Mesh::GetVertexCount() {
	return vertexCount;
}

