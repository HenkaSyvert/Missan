#include "core/gameobject.hpp"

#include "core/transform.hpp"

using namespace Missan;

namespace {

	// for generating unique IDs
	int idCounter = 1;

}

// PUBLIC
GameObject::GameObject(std::string aName) 
	: instanceID(idCounter++),
	name(aName) 
{
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
