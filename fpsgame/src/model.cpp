#include "model.h"


using namespace missan;

// PUBLIC

Mesh& Model::GetMesh() {
	return *mesh_ptr;
}

void Model::SetMesh(Mesh& mesh) {
	mesh_ptr = &mesh;
}

Texture& Model::GetTexture() {
	return *texture_ptr;
}

void Model::SetTexture(Texture& tex) {
	texture_ptr = &tex;
}

Model::Model(Mesh& mesh) {
	mesh_ptr = &mesh;
}

Model::Model(Mesh& mesh, Texture& texture) {
	mesh_ptr = &mesh;
	texture_ptr = &texture;
}