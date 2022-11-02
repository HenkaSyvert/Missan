#include "gameobject.hpp"

#include "physics/transform.hpp"

#include <string>

using namespace Missan;
using namespace std;


GameObject::GameObject() {
	name = "Game Object";
}

GameObject::~GameObject() {
	for (Component* c : components) 
		delete c;
}

GameObject::GameObject(GameObject& copy) {
	for (Component* c : copy.components) {
		components.push_back(c->Clone());
		components.back()->gameObject = this;
	}
	name = copy.name;
}
