#include "core/scene.hpp"

using namespace Missan;

// PUBLIC
Scene::~Scene() {
    for (GameObject* g : gameObjects)
        delete g;
}
