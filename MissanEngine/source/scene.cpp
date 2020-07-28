#include "scene.hpp"

using namespace missan;

// PUBLIC
Scene::~Scene() {
    for (GameObject* g : gameObjects)
        delete g;
}
