#include "gameobject.h"

using namespace missan;

// PUBLIC
Transform& GameObject::GetTransform() {
	return transform;
}

Mesh& GameObject::GetMesh() {
	return *mesh_ptr;
}

void GameObject::SetMesh(Mesh& mesh) {
	mesh_ptr = &mesh;
}

Texture& GameObject::GetTexture() {
	return *texture_ptr;
}

void GameObject::SetTexture(Texture& tex) {
	texture_ptr = &tex;
}
