#include "ecs/gameobject.hpp"
#include "ecs/component.hpp"

#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>

#include "util/packedassociativearray.hpp"

using namespace Missan;
using namespace std;



PackedAssociativeArray GameObject::gameObjects(sizeof(GameObject));
vector<size_t> GameObject::gameObjectsToDestroy;

// generate new unique ID or reuse an old one
static size_t GetUniqueId() {
	static size_t newId = 0;
	static queue<size_t> freeIds;

	if (freeIds.empty()) return newId++;

	size_t id = freeIds.front();
	freeIds.pop();

	return id;
}

size_t GameObject::Instantiate() {
	size_t id = GetUniqueId();
	GameObject g;
	g.id = id;
	gameObjects.Add(id, &g);
	return id;
}

size_t GameObject::Instantiate(size_t originalId) {
	size_t id = Instantiate();

	// copy original gameobject's components
	for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
		void* component = Component::GetById(originalId, componentTypeId);
		if (component) {
			size_t componentSize = Component::GetArrayById(componentTypeId)->elementSize;
			Component::AddById(id, componentTypeId, componentSize, component);
		}
	}

	return id;
}

void GameObject::Destroy(size_t gameObjectId) {
	gameObjectsToDestroy.push_back(gameObjectId);
}

void GameObject::DestroyImmediate(size_t gameObjectId) {
	for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
		((Component*)Component::GetById(gameObjectId, componentTypeId))->OnDestroy();
		Component::RemoveById(gameObjectId, componentTypeId);
	}
}