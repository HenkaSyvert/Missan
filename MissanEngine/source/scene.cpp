#include "scene.hpp"

#include "components/component.hpp"

using namespace missan;

// PUBLIC
Scene::~Scene() {
    for (GameObject* g : gameObjects)
        delete g;
}

GameObject& Scene::Instantiate(GameObject& prefab) {
    gameObjects.push_back(new GameObject(prefab));
    return *gameObjects.back();
}

