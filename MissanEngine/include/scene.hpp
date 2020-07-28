#pragma once

#include "missanpch.hpp"
#include "gameobject.hpp"

namespace missan {

	// Holds instaniated GameObjects
	class Scene {

	public:

		// The GameObjects in the Scene
		std::vector<GameObject*> gameObjects;

		// Deletes all contained GameObjects
		~Scene();


	};

}