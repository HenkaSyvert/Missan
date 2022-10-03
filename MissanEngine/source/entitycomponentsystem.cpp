#include "entitycomponentsystem.hpp"
#include "gameobject.hpp"
#include "component.hpp"

#include <queue>


using namespace Missan;
using namespace std;




static vector<GameObject*> gameObjectsToBeInstantiated;
static vector<GameObject*> gameObjectsToBeDestroyed;
static vector<GameObject*> gameObjects;


void EcsComponentsStart() {
	for (auto* g : gameObjects) for (auto* c : g->components) c->Start();
}

void EcsComponentsUpdate() {
	for (auto* g : gameObjects) for (auto* c : g->components) c->Update();
}

void EcsComponentsLateUpdate() {
	for (auto* g : gameObjects) for (auto* c : g->components) c->LateUpdate();
}

void EcsGameObjectInstantiate() {
	for (auto* g : gameObjectsToBeInstantiated) {
		gameObjects.push_back(g);
		for (auto* c : g->components) c->Start();
	}
	gameObjectsToBeInstantiated.clear();
}

void EcsGameObjectDestroy() {
	for (auto* g : gameObjectsToBeDestroyed) {
		bool found = false;

		for (Component* c : g->components) c->OnDestroy();

		for (unsigned int i = 0; !found && i < gameObjects.size(); i++) {
			if (g == gameObjects[i]) {
				gameObjects.erase(gameObjects.begin() + i);
				delete g;
				found = true;
			}

		}
	}
	gameObjectsToBeDestroyed.clear();
}

GameObject* GameObject::Instantiate(GameObject& original) {
	gameObjectsToBeInstantiated.push_back(new GameObject(original));
	return gameObjectsToBeInstantiated.back();
}

void GameObject::Destroy(GameObject* gameObject) {
	gameObjectsToBeDestroyed.push_back(gameObject);
}

vector<GameObject*>& EcsGetGameObjects() {
	return gameObjects;
}

