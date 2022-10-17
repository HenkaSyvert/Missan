#pragma once

#include "inspectable.hpp"
#include "memory/object.hpp"
#include "memory/memory.hpp"
#include "ecs/ecs.hpp"

namespace Missan {


	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class Component : public Object {

	public:

		/// 
		/// The GameObject this Component is attached to. 
		InstanceId gameObjectId = NULL;


		///
		/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(InstanceId otherGameObjectId) {}

		///
		/// Called every frame
		inline virtual void Update() {}

		///
		/// Called every frame, but after all regular Update events
		inline virtual void LateUpdate() {}

		///
		/// Called during GUI rendering
		inline virtual void OnGui() {}

		///
		/// Called prior to the GameObject being destroyed
		inline virtual void OnDestroy() {}



		template<class T>
		inline static InstanceId Add(InstanceId gameObjectId) {
			return ECS::AddComponent(Memory::GetTypeId<T>(), gameObjectId);
		}

		template<class T>
		inline InstanceId AddComponent() {
			return Add<T>(gameObjectId);
		}



		template<class T>
		inline static T* Get(InstanceId gameObjectId) {
			return (T*)ECS::GetComponent(Memory::GetTypeId<T>(), gameObjectId);
		}

		template<class T>
		inline T* GetComponent() {
			return Get<T>(gameObjectId);
		}



		template<class T>
		inline static void Remove(InstanceId gameObjectId) {
			ECS::RemoveComponent(Memory::GetTypeId<T>(), gameObjectId);
		}

		template<class T>
		inline void RemoveComponent() {
			Remove<T>(gameObjectId);
		}



		inline static RawArray<Component*> GetAttachedComponents(InstanceId gameObjectId) {
			return ECS::GetAttachedComponents(gameObjectId);
		}

	};
}
