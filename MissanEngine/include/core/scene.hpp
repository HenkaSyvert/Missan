#pragma once

#include "missanpch.hpp"
#include "core/gameobject.hpp"

namespace Missan {

	// Holds instaniated GameObjects
	class Scene {

	public:

		// The GameObjects in the Scene
		std::vector<GameObject*> gameObjects;

		// Deletes Scene and all contained GameObjects
		~Scene();
		
	};

}