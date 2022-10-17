#include "ecs/ecs.hpp"
#include "ecs/gameobject.hpp"
#include "ecs/component.hpp"

#include <vector>

using namespace Missan;
using namespace std;


vector<InstanceId> gameObjectsToDestroy;


InstanceId ECS::Instantiate(InstanceId originalGameObjectId) {

	InstanceId id = Memory::New<GameObject>();

	if (originalGameObjectId) {

		GameObject* original = Memory::Get<GameObject>(originalGameObjectId);
		GameObject* newGameObj = Memory::Get<GameObject>(id);

		for (auto& pair : original->components) {
			void* originalComp = Memory::GetByTypeId(pair.first, pair.second);
			AddComponent(pair.first, id, originalComp);
		}

	}

	return id;
}



InstanceId ECS::AddComponent(TypeId componentTypeId, InstanceId gameObjectId, void* originalComponent) {

	InstanceId compId = Memory::NewByTypeId(componentTypeId, originalComponent);
	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	g->components[componentTypeId] = compId;

	Component* comp = (Component*)Memory::GetByTypeId(componentTypeId, compId);
	comp->gameObjectId = gameObjectId;
	comp->Start();

	return compId;
}



void* ECS::GetComponent(TypeId componentTypeId, InstanceId gameObjectId) {
	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	return Memory::GetByTypeId(componentTypeId, g->components[componentTypeId]);
}



void ECS::RemoveComponent(TypeId componentTypeId, InstanceId gameObjectId) {
	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	InstanceId compId = g->components[componentTypeId];
	Component* comp = (Component*)Memory::GetByTypeId(componentTypeId, compId);
	comp->OnDestroy();
	Memory::DeleteByTypeId(componentTypeId, compId);
	g->components.erase(componentTypeId);
}



void ECS::Destroy(InstanceId gameObjectId) {
	gameObjectsToDestroy.push_back(gameObjectId);
}

void ECS::DestroyImmediate(InstanceId gameObjectId) {
	GameObject* g = Memory::Get<GameObject>(gameObjectId);
	for (auto& pair : g->components)
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
	for (auto& pair : g->components) {
		Component* c = (Component*)Memory::GetByTypeId(pair.first, pair.second);
		v.push_back(c);
	}

	return RawArray<Component*>(v.data(), v.size(), true);

}





void ECS::UpdateAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		Component* c = (Component*)arr[i];
		c->Update();
	}
}

void ECS::LateUpdateAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		Component* c = (Component*)arr[i];
		c->LateUpdate();
	}
}

void ECS::OnGuiAll() {
	for (int i = Memory::componentOffset; i < Memory::arrays.size(); i++) {
		auto arr = Memory::AsRawArrayByTypeId(i);
		Component* c = (Component*)arr[i];
		c->OnGui();
	}
}


