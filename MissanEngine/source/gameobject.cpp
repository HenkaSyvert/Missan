#include "gameobject.hpp"

#include "components/transform.hpp"

using namespace missan;

namespace {

	// for generating unique IDs
	int idCounter = 1;

}

// PUBLIC
GameObject::GameObject() : instanceID(idCounter++) {
	AddComponent<Transform>();
}

GameObject::~GameObject() {
	for (Component* c : components)
		delete c;
}

GameObject::GameObject(GameObject& copy) : instanceID(idCounter++) {
	for (Component* c : copy.components) {
		components.push_back(c->Clone());
		components.back()->AttachToGameObject(*this);
	}
}
