#include "scene.hpp"

#include "component.hpp"

using namespace missan;

// PUBLIC

GameObject& Scene::Instantiate(GameObject& prefab) {
    gameObjects.push_back(new GameObject(prefab));
    for (Component* c : gameObjects.back()->components)
        c->gameObject_ptr = gameObjects.back();
    return *gameObjects.back();
}

std::vector<GameObject*>& Scene::GetGameObjects() {
    return gameObjects;
}

