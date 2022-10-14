#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "ecs/packedassociativearray.hpp"
#include "ecs/rawarray.hpp"

#define DEBUG_COMPONENT 1

using namespace Missan;
using namespace std;



void Component::Copy(IdType destinationId, IdType sourceId) {
	ECS::Copy(destinationId, sourceId);
	RawArray<Component*> newComps = ECS::GetAll<Component>(destinationId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->Start();
}

void Component::Destroy(IdType gameObjectId) {
	RawArray<Component*> newComps = ECS::GetAll<Component>(gameObjectId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->OnDestroy();
	ECS::RemoveAll(gameObjectId);

}

RawArray<Component*> Component::GetAttachedComponents(IdType gameObjectId) {
	return ECS::GetAll<Component>(gameObjectId);
}

void Component::UpdateAll() {
	for (int j = ECS::componentOffset; j < ECS::arrays.size(); j++) {
		auto compArr = ECS::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->Update();
	}
}

void Component::LateUpdateAll() {
	for (int j = ECS::componentOffset; j < ECS::arrays.size(); j++) {
		auto compArr = ECS::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->LateUpdate();
	}
}

void Component::OnGuiAll() {
	for (int j = ECS::componentOffset; j < ECS::arrays.size(); j++) {
		auto compArr = ECS::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->OnGui();
	}
}