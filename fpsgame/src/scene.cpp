#include "scene.h"

using namespace missan;

void Scene::Instantiate(GameObject& go) {
	gameObjects.push_back(go);
}

std::vector<GameObject>& Scene::GetGameObjects() {
	return gameObjects;
}
