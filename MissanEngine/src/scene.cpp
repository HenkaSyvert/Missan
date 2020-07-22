#include "scene.hpp"

using namespace missan;

// PUBLIC

GameObject& Scene::Instantiate(GameObject& prefab) {
    gameObjects.push_back(prefab);
    return gameObjects.back();
}

std::vector<GameObject>& Scene::GetGameObjects() {
    return gameObjects;
}

