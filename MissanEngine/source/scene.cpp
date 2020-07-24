#include "scene.hpp"

#include "components/component.hpp"

using namespace missan;

// PUBLIC
Scene::~Scene() {
    for (GameObject* g : gameObjects_)
        delete g;
}

GameObject& Scene::Instantiate(GameObject& prefab) {
    gameObjects_.push_back(new GameObject(prefab));
    return *gameObjects.back();
}

void Scene::Update() {
    for (GameObject* g : gameObjects_)
        g->Update();
}
