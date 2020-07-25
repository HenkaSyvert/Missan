#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "gameobject.hpp"

namespace missan {

	class Scene {

		// TODO, cleanup gameobjects memory

	public:
		std::vector<GameObject*> gameObjects;

	public:
		~Scene();

		GameObject& Instantiate(GameObject& prefab);


	};

}