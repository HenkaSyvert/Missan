#pragma once

#include "component.hpp"
#include "memory/object.hpp"

#include <vector>
#include <string>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject : public Object {

	public:

		template<class T> inline void AddComponent() {
			Component::Add<T>(id);
		}


		// instantiate new game object and return ID
		static IdType Instantiate();
		static IdType Instantiate(IdType original);

		// add gameobject to queue to destroy at end of frame
		static void Destroy(IdType gameObjectId);

		// actually destroys gameobject, immediately. 
		static void DestroyImmediate(IdType gameObjectId);

		static std::vector<IdType> gameObjectsToDestroy;

		// TODO: add more primitives, like cylinder, capsule
		enum class PrimitiveType { sphere, cube, plane };
		static IdType CreatePrimitive(PrimitiveType type);

	};

}