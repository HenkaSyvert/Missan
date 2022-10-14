#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "memory/memory.hpp"

#define DEBUG_COMPONENT 1

using namespace Missan;
using namespace std;



void Component::Copy(IdType destinationId, IdType sourceId) {
	Memory::Copy(destinationId, sourceId);
	RawArray<Component*> newComps = Memory::GetAll<Component>(destinationId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->Start();
}

void Component::Destroy(IdType gameObjectId) {
	RawArray<Component*> newComps = Memory::GetAll<Component>(gameObjectId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->OnDestroy();
	Memory::RemoveAll(gameObjectId);

}

RawArray<Component*> Component::GetAttachedComponents(IdType gameObjectId) {
	return Memory::GetAll<Component>(gameObjectId);
}

void Component::UpdateAll() {
	for (int j = Memory::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->Update();
	}
}

void Component::LateUpdateAll() {
	for (int j = Memory::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->LateUpdate();
	}
}

void Component::OnGuiAll() {
	for (int j = Memory::componentOffset; j < Memory::arrays.size(); j++) {
		auto compArr = Memory::arrays[j];
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->OnGui();
	}
}