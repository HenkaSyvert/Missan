#pragma once


#include <unordered_map>
#include <queue>
#include <string>
#include <typeinfo>
#include <iostream>






#define MAX_GAME_OBJECTS 100



class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void GameObjectDestroyed(size_t gameObjectId) = 0;

};

template<typename T>
class ComponentArray : public IComponentArray {

public:
	T componentArray[MAX_GAME_OBJECTS];
	std::unordered_map<size_t, size_t> goToIndex;
	std::unordered_map<size_t, size_t> indexToGo;
	size_t size = 0;

	void InsertData(size_t gameObjectId) {

		size_t componentId = size++;
		goToIndex[gameObjectId] = componentId;
		indexToGo[componentId] = gameObjectId;
		componentArray[componentId] = T();

	}

	void RemoveData(size_t gameObjectId) {

		size_t indexOfRemoved = goToIndex[gameObjectId];
		size_t indexOfLast = size - 1;
		componentArray[indexOfRemoved] = componentArray[indexOfLast];

		size_t lastGoId = indexToGo[indexOfLast];
		goToIndex[lastGoId] = indexOfRemoved;
		indexToGo[indexOfRemoved] = lastGoId;

	}

	T* GetData(size_t gameObjectId) {
		return &componentArray[goToIndex[gameObjectId]];
	}

	void GameObjectDestroyed(size_t gameObjectId) {
		RemoveData(gameObjectId);
	}

};


class ComponentManager {
public:
	std::unordered_map<size_t, IComponentArray*> componentArrays;

	template<typename T>
	T* AddComponent(size_t gameObjectId) {

		size_t componentTypeId = typeid(T).hash_code();

		if (componentArrays.find(componentTypeId) == componentArrays.end()) {
			std::cout << "register new component type\n";
			componentArrays[componentTypeId] = new ComponentArray<T>();
		}

		((ComponentArray<T>*)componentArrays[componentTypeId])->InsertData(gameObjectId);

		std::cout << "added new comp of type " << typeid(T).name() << " to gameobj " << std::to_string(gameObjectId) << "\n";

		return ((ComponentArray<T>*)componentArrays[componentTypeId])->GetData(gameObjectId);
	}

	template<typename T>
	void RemoveComponent(size_t gameObjectId) {
		componentArrays[typeid(T).hash_code()]->RemoveData(gameObjectId);
	}

	template<typename T>
	T* GetComponent(size_t gameObjectId) {
		return &componentArrays[typeid(T).hash_code()]->GetData(gameObjectId);
	}
};

extern ComponentManager componentManager;
