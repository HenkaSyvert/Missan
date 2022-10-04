#include "gameobject.hpp"
#include "ecs.hpp"

#include <string>
#include <queue>
#include <iostream>

using namespace Missan;
using namespace std;


static size_t newId = 0;
static queue<size_t> freeIds;


GameObject::GameObject() {
	
	if (!freeIds.empty()) {
		_id = freeIds.front();
		freeIds.pop();
	}
	else {
		_id = newId++;
	}

	name = "Game Object " + to_string(_id);
}

GameObject::GameObject(GameObject& copy) : GameObject() {
	ECS::CopyComponents(copy.id, id);
	name = copy.name + to_string(id);
}

GameObject::~GameObject() {
	ECS::DestroyGameObject(id);
	freeIds.push(id);
}

