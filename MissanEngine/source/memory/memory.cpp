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