#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "util/packedassociativearray.hpp"

#define DEBUG_COMPONENT 1

using namespace Missan;
using namespace std;



static vector<PackedAssociativeArray*> componentArrays;

size_t Component::numberOfTypes = 0;
vector<string> Component::typeNames;
static inline bool IsComponentTypeRegistered(size_t componentTypeId) {
	return componentTypeId < componentArrays.size();
}


void Component::RegisterById(size_t componentTypeId, size_t componentSize) {
	if (IsComponentTypeRegistered(componentTypeId)) return;
	if (DEBUG_COMPONENT) cout << "RegisterById: componentArrays[" << componentTypeId << "] = " << GetNameById(componentTypeId) << "\n";
	componentArrays.push_back(new PackedAssociativeArray(componentSize));
}


PackedAssociativeArray* Component::GetArrayById(size_t componentTypeId) {

	if (IsComponentTypeRegistered(componentTypeId)) return componentArrays[componentTypeId];

	if (DEBUG_COMPONENT) cout << "GetArrayById: " << GetNameById(componentTypeId) << " is not registered, can't get array\n";
	return nullptr;
}

void Component::AddById(size_t gameObjectId, size_t componentTypeId, size_t componentSize, void* component) {

	if (DEBUG_COMPONENT) cout << "AddById: " << componentTypeId << ": " << GetNameById(componentTypeId) << "[gameobj ID: " << gameObjectId << "]\n";
	componentArrays[componentTypeId]->Add(gameObjectId, component);
	// change return type to avoid all casts??
	// TODO: also, might not be a good idea to call start here? or maybe?
	((Component*)GetById(gameObjectId, componentTypeId))->gameObjectId = gameObjectId;
	((Component*)GetById(gameObjectId, componentTypeId))->Start();
}

void Component::RemoveById(size_t gameObjectId, size_t componentTypeId) {

	if (!IsComponentTypeRegistered(componentTypeId))
		if (DEBUG_COMPONENT) cout << "RemoveById: " << componentTypeId << ": " << GetNameById(componentTypeId) << "[gameobj ID: " << gameObjectId << "] = NULL, cant remove\n";

	componentArrays[componentTypeId]->Remove(gameObjectId);
}

void* Component::GetById(size_t gameObjectId, size_t componentTypeId) {
	return componentArrays[componentTypeId]->GetById(gameObjectId);
}

void Component::Copy(size_t destinationId, size_t sourceId) {
	for (size_t componentTypeId = 0; componentTypeId < numberOfTypes; componentTypeId++) {
		void* component = GetById(sourceId, componentTypeId);
		if (component) {
			size_t componentSize = componentArrays[componentTypeId]->elementSize;
			AddById(destinationId, componentTypeId, componentSize, component);
		}
	}
}