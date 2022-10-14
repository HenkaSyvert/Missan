#pragma once

#include "inspectable.hpp"
#include "database.hpp"
#include "object.hpp"

#include <string>
#include <typeinfo>
#include <vector>

namespace Missan {


	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class Component : public Object {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		IdType gameObjectId = NULL;

		///
		/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(IdType otherGameObjectId) {}

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
		inline T* GetComponent() { return Component::Get<T>(gameObjectId); }




		template<class T> 
		inline static RawArray<T> GetRawArray() {
			return ECS::AsRawArray<T>();
		}

		static RawArray<Component*> GetAttachedComponents(IdType gameObjectId);

		// Create new component and attach to gameobject
		template<class T> 
		inline static void Add(IdType gameObjectId) {
			ECS::Add<T>(gameObjectId);
			ECS::Get<T>(gameObjectId)->gameObjectId = gameObjectId;
			ECS::Get<T>(gameObjectId)->Start();
		}

		// remove component from gameobject
		template<class T> 
		inline static void Remove(IdType gameObjectId) {
			ECS::Get<T>(gameObjectId)->OnDestroy();
			ECS::Remove<T>(gameObjectId);
		}


		template<class T> 
		inline static T* Get(IdType gameObjectId) {
			return ECS::Get<T>(gameObjectId);
		}

		static void Copy(IdType destinationId, IdType sourceId);
		static void Destroy(IdType gameObjectId);

		static void UpdateAll();
		static void LateUpdateAll();
		static void OnGuiAll();

		


	};
}
