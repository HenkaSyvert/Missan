#include "gameobject.hpp"

#include <string>
#include <queue>
#include <iostream>

using namespace Missan;
using namespace std;


size_t newId = 0;
queue<size_t> freeIds;


GameObject::GameObject() {
	
	cout << "GameObject(): ";
	if (!freeIds.empty()) {
		_id = freeIds.front();
		freeIds.pop();
		cout << "reuse old ";
	}
	else {
		_id = newId++;
	}
	cout << "ID: " << id << "\n";

	name = "Game Object " + to_string(_id);
}

GameObject::GameObject(GameObject& copy) : GameObject() {
	
	cout << "GameObject(*copy):\n";

	for (Component* c : copy.components) {
		components.push_back(c->Clone());
		components.back()->gameObject = this;
	}
	name = copy.name + to_string(id);
}

GameObject::~GameObject() {
	for (Component* c : components) 
		delete c;

	cout << "putting dead ID: " << id << " back into queue\n";
	freeIds.push(id);

}

