#include "memory/memory.hpp"
#include "internal.hpp"
#include "ecs/gameobject.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/material.hpp"

using namespace Missan;
using namespace std;


vector<ObjectArrayBase*> Memory::arrays;
size_t Memory::numberOfTypes = 0;
size_t Memory::componentOffset;

void Memory::Copy(size_t destinationId, size_t sourceId) {
	for (auto& table : arrays) if (table->Get(sourceId)) table->Add(destinationId, table->Get(sourceId));	
}

void Memory::RemoveAll(size_t id) {
	for (auto* table : arrays) table->Remove(id);
}

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
	componentOffset = numberOfTypes;
}