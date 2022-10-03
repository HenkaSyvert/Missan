#pragma once

// Thanks to Austin Morlan for inspiration
// https://austinmorlan.com/posts/entity_component_system/



#include <unordered_map>
#include <queue>
#include <string>
#include <typeinfo>
#include <iostream>

#include "gameobject.hpp"

#define MAX_GAME_OBJECTS 100



class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void EntityDestroyed(Missan::GameObject g) = 0;

};

template<typename T>
class ComponentArray : public IComponentArray {

public:
	T componentArray[MAX_GAME_OBJECTS];
	std::unordered_map<Missan::GameObject, size_t> goToIndex;
	std::unordered_map<size_t, Missan::GameObject> indexToGo;
	size_t size = 0;

	void InsertData(Missan::GameObject g, T component) {

		size_t compId = size++;
		goToIndex[g.id] = compId;
		indexToGo[compId] = g;
		componentArray[compId] = component;

	}

	void RemoveData(Missan::GameObject g) {

		size_t indexOfRemoved = goToIndex[g.id];
		size_t indexOfLast = size - 1;
		componentArray[indexOfRemoved] = componentArray[indexOfLast];

		size_t lastGoId = indexToGo[indexOfLast];
		goToIndex[lastGoId] = indexOfRemoved;
		indexToGo[indexOfRemoved] = lastGoId;

	}

	T& GetData(Missan::GameObject g) {
		return componentArray[goToIndex[g.id]];
	}

};


class ComponentManager {
public:

	std::unordered_map<std::string, size_t> componentTypes;
	std::unordered_map<std::string, IComponentArray*> componentArrays;



	template<typename T>
	void RegisterComponent() {

		std::string name = typeid(T).name();
		if (componentTypes.find(name))
			std::cout << "component type already registered\n";

		componentTypes.insert({ typeid(T).name, typeid(T).hash_code });

		componentArrays.insert({ name, new ComponentArray<T>() });


	}

	template<typename T>
	void AddComponent(Missan::GameObject g, T component) {
		componentArrays[typeid(T).name]->InsertData(g, component);

	}

	template<typename T>
	void RemoveComponent(Missan::GameObject g) {
		componentArrays[typeid(T).name]->RemoveData(g);
	}

	template<typename T>
	T& GetComponent(Missan::GameObject g) {
		return componentArrays[typeid(T).name]->GetData(g);
	}
};
