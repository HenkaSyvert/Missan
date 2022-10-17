#pragma once

#include "component.hpp"
#include "memory/object.hpp"

#include <vector>
#include <string>
#include <unordered_map>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject : public Object {

	public:

		template<class T> inline void AddComponent() {
			Component::Add<T>(instanceId);
		}

		std::unordered_map<size_t, InstanceId> components;



		// instantiate new game object and return ID
		static InstanceId Instantiate();
		static InstanceId Instantiate(InstanceId original);

		// add gameobject to queue to destroy at end of frame
		static void Destroy(InstanceId gameObjectId);

		// actually destroys gameobject, immediately. 
		static void DestroyImmediate(InstanceId gameObjectId);

		static std::vector<InstanceId> gameObjectsToDestroy;

		// TODO: add more primitives, like cylinder, capsule
		enum class PrimitiveType { sphere, cube, plane };
		static InstanceId CreatePrimitive(PrimitiveType type);

	};

}