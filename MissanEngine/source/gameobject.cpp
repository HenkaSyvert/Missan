#include "gameobject.hpp"

#include "components/transform.hpp"

using namespace missan;

// PUBLIC
GameObject::GameObject() {
	AddComponent<Transform>();
}

GameObject::~GameObject() {
	for (Component* c : components)
		delete c;
}

GameObject::GameObject(GameObject& copy) {
	for (Component* c : copy.components) {
		components.push_back(c->Clone());
		components.back()->AttachToGameObject(*this);
	}
}
