#pragma once

#include "inspectable.hpp"
#include "memory/object.hpp"
#include "memory/rawarray.hpp"
#include "memory/idtypes.hpp"

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
		static T* Add(InstanceId a) {
			return nullptr;
		}

		template<class T>
		static T* Get(InstanceId as) { return nullptr; }

		template<class T>
		T* GetComponent() { return nullptr; }

		static RawArray<Component*> GetAttachedComponents(size_t a) { return RawArray<Component*>(0, 0); }

		static void Copy(InstanceId t, InstanceId a){}
		static void Destroy(InstanceId t){}

		static void UpdateAll();
		static void LateUpdateAll();
		static void OnGuiAll();

		static size_t componentOffset;



	};
}
