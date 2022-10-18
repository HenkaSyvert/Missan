#include "ecs/ecs.hpp"
#include "ecs/gameobject.hpp"
#include "ecs/component.hpp"
#include "memory/idtypes.hpp"

#include <unordered_map>
#include <vector>

using namespace Missan;
using namespace std;


vector<InstanceId> gameObjectsToDestroy;

unordered_map<InstanceId, unordered_map<TypeId, InstanceId>> componentMap;


InstanceId ECS::Instantiate(InstanceId originalGameObjectId) {

	InstanceId id = Memory::New<GameObject>();

	if (originalGameObjectId) {


		for (auto& pair : componentMap[originalGameObjectId]) {
			void* originalComp = Memory::GetByTypeId(pair.first, pair.second);
			AddComponent(pair.first, id, originalComp);
		}

	}

	return id;
}



InstanceId ECS::AddComponent(TypeId componentTypeId, InstanceId gameObjectId, void* originalComponent) {

	InstanceId compId = Memory::NewByTypeId(componentTypeId, originalComponent);
	componentMap[gameObjectId][componentTypeId] = compId;

	Component* comp = (Component*)Memory::GetByTypeId(componentTypeId, compId);
	comp->gameObjectId = gameObjectId;
	comp->Start();

	return compId;
}



void* ECS::GetComponent(TypeId componentTypeId, InstanceId gameObjectId) {
	return Memory::GetByTypeId(componentTypeId, componentMap[gameObjectId][componentTypeId]);
}



void ECS::RemoveComponent(TypeId componentTypeId, InstanceId gameObjectId) {
	InstanceId compId = componentMap[gameObjectId][componentTypeId];
	Component* comp = (Component*)Memory::GetByTypeId(componentTypeId, compId);
	comp->OnDestroy();
	Memory::DeleteByTypeId(componentTypeId, compId);
	componentMap[gameObjectId].erase(componentTypeId);
}



void ECS::Destroy(InstanceId gameObjectId) {
	gameObjectsToDestroy.push_back(gameObjectId);
}

void ECS::DestroyImmediate(InstanceId gameObjectId) {
	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	for (auto& pair : componentMap[gameObjectId])
		RemoveComponent(pair.first, gameObjectId);
	Memory::Delete<GameObject>(gameObjectId);
}

void ECS::DestroyQueued() {
	for (auto id : gameObjectsToDestroy)
		DestroyImmediate(id);
	gameObjectsToDestroy.clear();
}




RawArray<Component*> ECS::GetAttachedComponents(InstanceId gameObjectId) {

	vector<Component*> v;

	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	for (auto& pair : componentMap[gameObjectId]) {
		Component* c = (Component*)Memory::GetByTypeId(pair.first, pair.second);
		v.push_back(c);
	}

	return RawArray<Component*>(v.data(), v.size(), true);

}





void ECS::UpdateAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		for (int j = 0; j < arr.count; j++) {
			Component* c = (Component*)arr[j];
			c->Update();
		}
	}
}

void ECS::LateUpdateAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		for (int j = 0; j < arr.count; j++) {
			Component* c = (Component*)arr[j];
			c->LateUpdate();
		}
	}
}

void ECS::OnGuiAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		for (int j = 0; j < arr.count; j++) {
			Component* c = (Component*)arr[j];
			c->OnGui();
		}
	}
}


