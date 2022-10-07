#include "ecs/gameobject.hpp"
#include "ecs/component.hpp"

#include <queue>
#include <unordered_map>
#include <stdlib.h>
#include <iostream>

#include "util/packedassociativearray.hpp"

#include "physics/transform.hpp"
#include "physics/collider.hpp"

#include "graphics/renderer.hpp"
#include "graphics/mesh.hpp"
#include "graphics/material.hpp"

#include "engine.hpp"

using namespace Missan;
using namespace std;



PackedAssociativeArray<GameObject> GameObject::gameObjects;
vector<size_t> GameObject::gameObjectsToDestroy;

// generate new unique ID or reuse an old one
static size_t GetUniqueId() {
	static size_t newId = 0;
	static queue<size_t> freeIds;

	if (freeIds.empty()) return newId++;

	size_t id = freeIds.front();
	freeIds.pop();

	return id;
}

size_t GameObject::Instantiate() {
	size_t id = GetUniqueId();
	gameObjects.Add(id);
	GameObject* g = gameObjects.Get(id);
	g->id = id;
	return id;
}

size_t GameObject::Instantiate(size_t originalId) {
	size_t id = Instantiate();
	Component::Copy(id, originalId);
	return id;
}

void GameObject::Destroy(size_t gameObjectId) {
	gameObjectsToDestroy.push_back(gameObjectId);
}

void GameObject::DestroyImmediate(size_t gameObjectId) {
	Component::Destroy(gameObjectId);
	gameObjectsToDestroy.clear();
}

size_t GameObject::CreatePrimitive(PrimitiveType type) {
	size_t id = GameObject::Instantiate();
	Component::Add<Transform>(id);
	
	Component::Add<Renderer>(id);
	Renderer* r = Component::Get<Renderer>(id);
	// TODO: add list of default materials.. 
	r->material = new Material();
	r->material->shader = Shader::diffuseSpecular;
	Component::Add<Collider>(id);
	Collider* c = Component::Get<Collider>(id);

	switch (type) {
	case PrimitiveType::cube:
		r->mesh = Resources::GetMesh("resources/meshes/cube.mesh");
		// c = different kind of collider?
		// TODO: add different kind of colliders.. 
		gameObjects.Get(id)->name = "Cube";
		break;
	case PrimitiveType::sphere:
		// todo...
		gameObjects.Get(id)->name = "Sphere";
		break;
	case PrimitiveType::plane:
		r->mesh = Resources::GetMesh("resources/meshes/plane.mesh");
		gameObjects.Get(id)->name = "Plane";
		// todo: ditto collider.. 
		break;
	}
	return id;
}