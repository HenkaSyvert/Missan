#include "gameobject.hpp"

using namespace missan;

// PUBLIC
GameObject::GameObject(){
	collider.SetTransform(transform);
}

GameObject::GameObject(Mesh& mesh, Texture& texture)
	: GameObject()
{
	SetMesh(mesh);
	SetTexture(texture);
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



Collider& GameObject::GetCollider() {
	return collider;
}