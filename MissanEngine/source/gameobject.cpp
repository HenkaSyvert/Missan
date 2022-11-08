#include "component.hpp"
#include "internal.hpp"

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
	std::cout << "~GameObject(): components.size() = " << components.size() << "\n";
	int i = 0;
	for (AbstractComponent* c : components) {

		std::cout << "components[" << i++ << "] = " << c << "\n";
		delete c;
	}
	std::cout << "destructor done, size = " << components.size() << std::endl;
}