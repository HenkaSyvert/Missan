#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "util/packedassociativearray.hpp"
#include "util/rawarray.hpp"

#define DEBUG_COMPONENT 1

using namespace Missan;
using namespace std;



vector<PackedAssociativeArrayBase*> Component::componentArrays;

size_t Component::numberOfTypes = 0;

void Component::Copy(size_t destinationId, size_t sourceId) {
	for (auto& compArr : componentArrays) {
		auto* component = compArr->Get(sourceId);
		if (component) compArr->Add(destinationId, component);
	}
}

void Component::Destroy(size_t gameObjectId) {
	for (auto& compArr : componentArrays)
		if (compArr->Get(gameObjectId)) compArr->Remove(gameObjectId);
}

RawArray<Component*> Component::GetAttachedComponents(size_t gameObjectId) {
	vector<Component*> comps;
	for (auto& componentArray : componentArrays){
		auto component = componentArray->Get(gameObjectId);
		if (component) comps.push_back((Component*)component);
	}
	return RawArray<Component*>(comps.data(), comps.size(), true);
}

void Component::UpdateAll() {
	for (auto& arr : componentArrays) {
		auto raw = arr->AsRawArrayBase();
		for (int i = 0; i < raw.count; i++)
			((Component*)raw[i])->Update();
	}
}

void Component::LateUpdateAll() {
	for (auto& arr : componentArrays) {
		auto raw = arr->AsRawArrayBase();
		for (int i = 0; i < raw.count; i++)
			((Component*)raw[i])->LateUpdate();
	}
}

void Component::OnGuiAll() {
	for (auto& arr : componentArrays) {
		auto raw = arr->AsRawArrayBase();
		for (int i = 0; i < raw.count; i++)
			((Component*)raw[i])->OnGui();
	}
}