#include "pch.hpp"
#include "ecs.hpp"
#include "internal.hpp"
#include "collision.hpp"
#include "collider.hpp"
#include "transform.hpp"
#include "renderer.hpp"
#include "engine.hpp"

using namespace Missan;
using namespace std;

vector<GameObject*> GameObject::instances;
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
		g->Start();
		GameObject::instances.push_back(g);
	}
	newGameObjects.clear();
}

void GameObject::Destroy(GameObject* gameObject) {
	deadGameObjects.push_back(gameObject);
}

void GameObjectDoDestructions() {
	for (auto* g : deadGameObjects) {
		g->OnDestroy();
		
		auto& gos = GameObject::instances;
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
	auto* c = g->AddComponent<Collider>();

	switch (type) {
	case PrimitiveType::Cube:
		r->mesh = Resources::GetMesh("../MissanEngine/data/meshes/cube.mesh");	
		c->shape = Collider::Shape::Box;
		g->name = "Cube";
		break;
	case PrimitiveType::Sphere:
		r->mesh = new Mesh(Resources::GenerateUvSphere(30, 30));
		c->shape = Collider::Shape::Sphere;
		g->name = "Sphere";
		break;
	}

	return g;
}

void GameObject::Start() {
	transform = GetComponent<Transform>();
	for (auto* c : components) {
		c->transform = transform;
		c->Start();
	}
}
void GameObject::OnCollisionEnter(Collision collision) { for (auto* c : components) c->OnCollisionEnter(collision); }
void GameObject::OnCollisionStay(Collision collision) { for (auto* c : components) c->OnCollisionStay(collision); }
void GameObject::OnCollisionExit(Collision collision) { for (auto* c : components) c->OnCollisionExit(collision); }
void GameObject::Update() { for (auto* c : components) c->Update(); }
void GameObject::LateUpdate() { for (auto* c : components) c->LateUpdate(); }
void GameObject::OnGui() { for (auto* c : components) c->OnGui(); }
void GameObject::OnDestroy() { for (auto* c : components) c->OnDestroy(); }
void GameObject::DisplayInInspector() { for (auto* c : components) c->DisplayInInspector(); }