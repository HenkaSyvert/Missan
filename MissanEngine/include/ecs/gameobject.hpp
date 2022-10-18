#pragma once

#include "memory/object.hpp"
#include "ecs/ecs.hpp"

#include <unordered_map>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject : public Object {

	public:

		GameObject() { name = "GameObject"; }

		inline static InstanceId Instantiate(InstanceId originalGameObjectId = NULL) {
			return ECS::Instantiate(originalGameObjectId);
		}

		inline static void Destroy(InstanceId gameObjectId) {
			ECS::Destroy(gameObjectId);
		}

		// TODO: add more primitives, like cylinder, capsule
		enum class PrimitiveType { sphere, cube, plane };
		static InstanceId CreatePrimitive(PrimitiveType type);

	};

}