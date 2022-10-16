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
queue<InstanceId> Memory::freeIds;

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
}

// generate new unique ID or reuse an old one
InstanceId Memory::GenerateUniqueInstanceId() {
	static InstanceId newId = 1;	// start count at 1 because 0 = NULL

	if (freeIds.empty()) return newId++;

	InstanceId id = freeIds.front();
	freeIds.pop();

	return id;
}