#include "memory/memory.hpp"
#include "internal.hpp"
#include "ecs/gameobject.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/material.hpp"

#include <queue>

using namespace Missan;
using namespace std;


vector<ObjectArrayBase*> Memory::arrays;
size_t Memory::componentOffset;

// IDs of dead objects, to be reused. 
static queue<InstanceId> freeIds;

void MemoryInitialize() {

	// need to register these in this order because number of asset times is constant, 
	// but number of components is unknown. allows to handle all component types separate
	// from assets. 

	using namespace Memory;

	//TODO: getting type ID registers new class, 
	// make into separate func
	GetTypeId<GameObject>();
	GetTypeId<Texture>();
	GetTypeId<Mesh>();
	GetTypeId<Shader>();
	GetTypeId<Material>();


	componentOffset = arrays.size();
}

// generate new unique ID or reuse an old one
static InstanceId GenerateUniqueInstanceId() {
	static InstanceId newId = 1;	// start count at 1 because 0 = NULL

	if (freeIds.empty()) return newId++;

	InstanceId id = freeIds.front();
	freeIds.pop();

	return id;
}


RawArrayBase Memory::AsRawArrayByTypeId(TypeId typeId) {
	return arrays[typeId]->AsRawArrayBase();
}


/// 
/// only use this one if you've already accessed the type array via
/// one of the templated funcs, otherwise it might not be created yet. 
InstanceId Memory::NewByTypeId(TypeId typeId, const void* const object) {
	InstanceId id = GenerateUniqueInstanceId();
	arrays[typeId]->Add(id, object);
	return id;
}

void* Memory::GetByTypeId(TypeId typeId, InstanceId id) {
	return arrays[typeId]->Get(id);
}

void Memory::SetByTypeId(TypeId typeId, InstanceId instanceId, const void* const data) {

}

void Memory::DeleteByTypeId(TypeId typeId, InstanceId id) {
	arrays[typeId]->Remove(id);
	freeIds.push(id);
}