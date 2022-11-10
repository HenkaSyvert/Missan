#include "component.hpp"
#include "internal.hpp"

#include "physics/collider.hpp"
#include "physics/transform.hpp"
#include "graphics/renderer.hpp"
#include "engine.hpp"

using namespace Missan;
using namespace std;

vector<GameObject*> GameObject::gameObjects;
static vector<GameObject*> newGameObjects;
static vector<GameObject*> deadGameObjects;

GameObject* GameObject::Instantiate(GameObject* original) {
	GameObject* g = new GameObject();
	newGameObjects.push_back(g);
	if (original) {
		g->name = original->name;
		for (auto* c : original->components) {
			auto newComp = c->Clone();
			g->components.push_back(newComp);
			newComp->gameObject = g;
		}

	}
	return g;
}

void GameObjectDoInstantiations() {
	for (auto* g : newGameObjects) {
		for (auto* c : g->components) c->Start();
		GameObject::gameObjects.push_back(g);
	}
	newGameObjects.clear();
}

void GameObject::Destroy(GameObject* gameObject) {
	deadGameObjects.push_back(gameObject);
}

void GameObjectDoDestructions() {
	for (auto* g : deadGameObjects) {
		for (auto* c : g->components) {
			c->OnDestroy();
			delete c;
		}
		auto& gos = GameObject::gameObjects;
		for (size_t i = 0; i < gos.size(); i++)
			if (gos[i] == g) gos.erase(gos.begin() + i);
		delete g;
	}
	deadGameObjects.clear();
}

GameObject::~GameObject() {
	for (AbstractComponent* c : components) delete c;	
}

GameObject* GameObject::InstantiatePrimitive(PrimitiveType type) {

	GameObject* g = Instantiate();
	g->AddComponent<Transform>();
	auto* r = g->AddComponent<Renderer>();
	r->material = new Material();
	r->material->texture = Resources::GetTexture("resources/textures/blank.png");
	r->material->shader = Shader::phong;
	auto* c = g->AddComponent<Collider>();

	switch (type) {
	case PrimitiveType::Cube:
		r->mesh = Resources::GetMesh("resources/meshes/cube.mesh");
		c->shape = Collider::Shape::aabb;
		g->name = "Cube";
		break;
	case PrimitiveType::Sphere:
		r->mesh = new Mesh(Resources::GenerateUvSphere(20, 20));
		c->shape = Collider::Shape::sphere;
		g->name = "Sphere";
		break;
	}

	return g;
}