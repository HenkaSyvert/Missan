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

// deep copy function to copy components
GameObject::GameObject(GameObject& copy) {

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



void GameObject::SetUpdateFunction(void (*func)(GameObject& go)) {
	UpdateFunc = func;
}

void GameObject::Update() {
	if (UpdateFunc != nullptr) UpdateFunc(*this);
}



Collider& GameObject::GetCollider() {
	return collider;
}


