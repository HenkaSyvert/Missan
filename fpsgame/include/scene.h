#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "gameobject.h"
#include "model.h"
#include "transform.h"

namespace missan {

	class Scene {

	private:
		std::vector<GameObject> gameObjects;

	public:
		void Instantiate(GameObject& go); //TODO

		std::vector<GameObject>& GetGameObjects();
	};

}
