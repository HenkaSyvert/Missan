#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "gameobject.hpp"

namespace missan {

	class Scene {

		// TODO, cleanup gameobjects memory

	private:
		std::vector<GameObject*> gameObjects_;

	public:
		~Scene();

		GameObject& Instantiate(GameObject& prefab);
		const std::vector<GameObject*>& gameObjects = gameObjects_;


		void Update();

	};

}