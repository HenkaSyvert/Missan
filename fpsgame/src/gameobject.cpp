#include "gameobject.hpp"

using namespace missan;

// PUBLIC
GameObject::GameObject() {

}

GameObject::GameObject(Mesh& mesh, Texture& texture){
	SetMesh(mesh);
	SetTexture(texture);
}

GameObject::GameObject(Mesh& mesh, Texture& texture, Transform& transform) {
	GameObject(mesh, texture);
	this->transform = transform;
}


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



void GameObject::SetUpdateFunction(void (*func)(GameObject& go, Input& input)) {
	UpdateFunc = func;
}

void GameObject::Update(Input& input) {
	if (UpdateFunc != nullptr) UpdateFunc(*this, input);
}