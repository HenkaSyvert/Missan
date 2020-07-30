#pragma once

#include "missanpch.hpp"
#include "gameobject.hpp"

// test
#include <array>
#include "core/component.hpp"
#include <map>
#include "core/transform.hpp"
#include "graphics/camera.hpp"
#include <string>




namespace Missan {

	// Holds instaniated GameObjects
	class Scene {

	public:

		// The GameObjects in the Scene
		std::vector<GameObject*> gameObjects;

		// Deletes all contained GameObjects
		~Scene();
		
		

		// TEST //////////////
#pragma region ENTITY_COMPONENT_SYSTEM

		// Maximum number of GameObjects allowed in a Scene
		static constexpr int MAX_GAMEOBJECTS = 1024;

		// Maximum number of Components allowed for each GameObject
		static constexpr int MAX_COMPONENTS = 64;

		// Keeps track of which kinds of Components are in the Scene
		std::map<std::string, Component*> componentRegistry;

		// Is this Component type registred?
		template <class T> bool IsComponentRegistered() {
			for (auto& str : componentRegistry)
				if (!str.first.compare(typeid(T).name()))
					return true;
			return false;
		}

		// Add this Component type to the registry
		template <class T> void RegisterComponent() {
			std::array<T*, MAX_GAMEOBJECTS>* arr = new std::array<T*, MAX_GAMEOBJECTS>;
			componentRegistry.emplace(typeid(T).name(), (Component*)arr);
			std::cout << "comp added\n";
		}


		template <class T> void CheckComponent() {
			if (!IsComponentRegistered<T>())
				RegisterComponent<T>();
		}

		void Test() {
			CheckComponent<Transform>();
			CheckComponent<Camera>();
			CheckComponent<Camera>();
		}

#pragma endregion

	};

}