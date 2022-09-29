#include "gameobject.hpp"

#include "physics/transform.hpp"

using namespace Missan;


GameObject::GameObject() {}

GameObject::~GameObject() {
	for (Component* c : components) 
		delete c;
}

GameObject::GameObject(GameObject& copy) {
	for (Component* c : copy.components) {
		components.push_back(c->Clone());
		components.back()->gameObject = this;
	}
}
