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



Database Component::componentArrays;


void Component::Copy(IdType destinationId, IdType sourceId) {
	componentArrays.Copy(destinationId, sourceId);
	RawArray<Component*> newComps = componentArrays.GetAll<Component>(destinationId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->Start();
}

void Component::Destroy(IdType gameObjectId) {
	RawArray<Component*> newComps = componentArrays.GetAll<Component>(gameObjectId);
	for (int i = 0; i < newComps.count; i++) newComps[i]->OnDestroy();
	componentArrays.RemoveAll(gameObjectId);

}

RawArray<Component*> Component::GetAttachedComponents(IdType gameObjectId) {
	return componentArrays.GetAll<Component>(gameObjectId);
}

void Component::UpdateAll() {
	for (auto* compArr : componentArrays.tables) {
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->Update();
	}
}

void Component::LateUpdateAll() {
	for (auto* compArr : componentArrays.tables) {
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->LateUpdate();
	}
}

void Component::OnGuiAll() {
	for (auto* compArr : componentArrays.tables) {
		RawArrayBase arr = compArr->AsRawArrayBase();
		for (int i = 0; i < arr.count; i++)
			((Component*)arr[i])->OnGui();
	}
}