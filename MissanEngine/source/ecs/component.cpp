#include "ecs/component.hpp"

#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>

#include "util/packedassociativearray.hpp"

using namespace Missan;
using namespace std;



static vector<PackedAssociativeArray*> componentArrays;

size_t Component::numberOfTypes = 0;
static inline bool IsComponentTypeRegistered(size_t componentTypeId) {
	return componentTypeId < componentArrays.size();
}


void Component::RegisterById(size_t componentTypeId, size_t componentSize) {
	if (IsComponentTypeRegistered(componentTypeId)) return;
	cout << "register new component ID: " << componentTypeId << "\n";
	componentArrays.push_back(new PackedAssociativeArray(componentSize));
}


PackedAssociativeArray* Component::GetArrayById(size_t componentTypeId) {

	if (IsComponentTypeRegistered(componentTypeId)) return componentArrays[componentTypeId];

	cout << "component ID: " << componentTypeId << " is not registered, cant get array\n";
	return nullptr;
}

void Component::AddById(size_t gameObjectId, size_t componentTypeId, size_t componentSize, void* component) {

	cout << "addByid(): goid: " << gameObjectId << " compId: " << componentTypeId << " compsize: " << componentSize << "\n";
	cout << "componentArrays.size(): " << componentArrays.size() << "\n";
	componentArrays[componentTypeId]->Add(gameObjectId, component);
	// change return type to avoid all casts??
	// TODO: also, might not be a good idea to call start here? or maybe?
	((Component*)GetById(gameObjectId, componentTypeId))->gameObjectId = gameObjectId;
	((Component*)GetById(gameObjectId, componentTypeId))->Start();
}

void Component::RemoveById(size_t gameObjectId, size_t componentTypeId) {

	if (!IsComponentTypeRegistered(componentTypeId))
		cout << "component ID: " << componentTypeId << " is not registered, cant remove element\n";

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