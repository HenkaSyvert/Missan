#pragma once

#include "ecs/component.hpp"
#include "util/packedassociativearray.hpp"

#include <vector>
#include <string>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject {

	public:
		size_t id; // TODO: consider making id = 0 sentinel value for uninstantiated or smth
		// TODO: typedef size_t into something more descriptive.. 
		std::string name = "Game Object";


		template<class T> void AddComponent() {
			Component::Add<T>(id);
		}


		// instantiate new game object and return ID
		static size_t Instantiate();
		static size_t Instantiate(size_t original);

		// add gameobject to queue to destroy at end of frame
		static void Destroy(size_t gameObjectId);

		// actually destroys gameobject, immediately. 
		static void DestroyImmediate(size_t gameObjectId);

		static PackedAssociativeArray gameObjects;
		static std::vector<size_t> gameObjectsToDestroy;
		
		// TODO: these convenient functions are dangerous since pointer can be invalidated if any gameobject is created/destroyed.. 
		static GameObject* GetGameObject(size_t id);

		// TODO: add more primitives, like cylinder, capsule
		enum class PrimitiveType { sphere, cube, plane };
		static size_t CreatePrimitive(PrimitiveType type);

	};

}