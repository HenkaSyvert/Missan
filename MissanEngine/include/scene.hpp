#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "gameobject.hpp"

namespace missan {

	class Scene {

	public:
        std::vector<GameObject> gameObjects;

	public:
        GameObject& Instantiate(GameObject& prefab);

		std::vector<GameObject>& GetGameObjects();

	};

}