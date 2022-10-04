#include "ecs.hpp"

#include <unordered_map>
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace Missan;
using namespace std;

size_t ECS::freeComponentTypeId = 0;
class ComponentArray {

public:
	char* data;
	unordered_map<size_t, size_t> idToIndex;
	unordered_map<size_t, size_t> indexToId;
	size_t elementSize;
	size_t count = 0;
	string typeName;
	static constexpr size_t DEFAULT_CAPACITY = 2;
	size_t capacity = DEFAULT_CAPACITY;

	ComponentArray(size_t elementSize, string typeName) {
		this->elementSize = elementSize;
		this->typeName = typeName;
		data = (char*)malloc(elementSize * DEFAULT_CAPACITY);
	}

	void* Add(size_t gameObjectId, void* component) {
		cout << "Add " << typeName << "[" << gameObjectId << "]\n";
		
		if (idToIndex.find(gameObjectId) != idToIndex.end()) {
			cout << "already has this component\n";
			return nullptr;
		}

		size_t index = count++;
		if (count > capacity) {
			cout << "needs resize\n";
			data = (char*)realloc(data, capacity * 2);
		}

		indexToId[index] = gameObjectId;
		idToIndex[gameObjectId] = index;

		void* newComponent = data + elementSize * index;
		memcpy(newComponent, component, elementSize);
		return newComponent;
	}

	void Remove(size_t gameObjectId) {
		cout << "Remove " << typeName << "[" << gameObjectId << "]\n";

		if (idToIndex.find(gameObjectId) == idToIndex.end()) {
			cout << "does not have this component, cant remove\n";
			return;
		}

		size_t indexOfRemoved = idToIndex[gameObjectId];
		size_t idOfLast = indexToId[count - 1];

		void* removedComponent = data + elementSize * indexOfRemoved;
		void* lastComponent = data + elementSize * (count - 1);
		memcpy(removedComponent, lastComponent, elementSize);

		idToIndex[idOfLast] = indexOfRemoved;
		indexToId[indexOfRemoved] = idOfLast;

		indexToId.erase(count - 1);
		idToIndex.erase(gameObjectId);
		
		count--;

	}

	void* Get(size_t gameObjectId) {
		cout << "Get " << typeName << "[" << gameObjectId << "]\n";
		
		if (idToIndex.find(gameObjectId) == idToIndex.end()) {
			cout << "does not exist\n";
			return nullptr;
		}

		size_t index = idToIndex[gameObjectId];
		return data + elementSize + index;

	}

};


static unordered_map<size_t, ComponentArray*> componentArrays;


const void* ECS::GetComponentArrayById(size_t componentTypeId) {

	if (componentArrays.find(componentTypeId) == componentArrays.end()) {
		cout << "component array " << to_string(componentTypeId) << " does not exist";
		return nullptr;
	}
	else return &componentArrays[componentTypeId]->data;

}

void* ECS::AddComponentById(size_t gameObjectId, size_t componentTypeId, size_t componentSize, string componentName, void* component) {

	if (componentArrays.find(componentTypeId) == componentArrays.end()) {
		std::cout << "register new component type\n";
		componentArrays[componentTypeId] = new ComponentArray(componentSize, componentName);
	}

	return componentArrays[componentTypeId]->Add(gameObjectId, component);
}

void ECS::RemoveComponentById(size_t gameObjectId, size_t componentTypeId) {
	componentArrays[componentTypeId]->Remove(gameObjectId);
}

void* ECS::GetComponentById(size_t gameObjectId, size_t componentTypeId) {
	return componentArrays[componentTypeId]->Get(gameObjectId);
}

void ECS::CopyComponents(size_t sourceId, size_t destinationId) {
	for (auto& pair : componentArrays) {
		ComponentArray* componentArray = pair.second;
		void* component = componentArray->Get(sourceId);
		if (component) componentArray->Add(destinationId, component);
	}
}

void ECS::DestroyGameObject(size_t gameObjectId) {
	for (auto& pair : componentArrays) {
		pair.second->Remove(gameObjectId);
	}
}