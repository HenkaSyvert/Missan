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

GameObject::GameObject(GameObject& copy) {
	std::vector<class Component*> newComponents;
	for (Component* c : copy.components) {
		newComponents.push_back(c->Clone());
	}
	components = newComponents;
	for (Component* c : components) {
		c->AttachToGameObject(*this);
	}

	// temporary until component system is done
	transform = copy.transform;
	mesh_ptr = copy.mesh_ptr;
	texture_ptr = copy.texture_ptr;
	collider = copy.collider;

}

GameObject::~GameObject() {
	for (Component* c : components)
		delete c;
}


Transform& GameObject::GetTransform() {
	return transform;
}



Mesh& GameObject::GetMesh() const {
	return *mesh_ptr;
}

void GameObject::SetMesh(Mesh& mesh) {
	mesh_ptr = &mesh;
}



Texture& GameObject::GetTexture()const {
	return *texture_ptr;
}

void GameObject::SetTexture(Texture& tex) {
	texture_ptr = &tex;
}


std::vector<Component*>& GameObject::GetComponents() {
	return components;
}



Collider& GameObject::GetCollider() {
	return collider;
}


