#pragma once

#include "component.hpp"
#include "util/packedassociativearray.hpp"

#include <vector>
#include <string>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject {

	public:
		size_t id; // TODO: consider making id = 0 sentinel value for uninstantiated or smth
		std::string name = "Game Object";


		// instantiate new game object and return ID
		static size_t Instantiate();
		static size_t Instantiate(size_t original);

		// add gameobject to queue to destroy at end of frame
		static void Destroy(size_t gameObjectId);

		// actually destroys gameobject, immediately. 
		static void DestroyImmediate(size_t gameObjectId);

		static PackedAssociativeArray gameObjects;
		static std::vector<size_t> gameObjectsToDestroy;
	};

}