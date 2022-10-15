#pragma once

#include "inspectable.hpp"
#include "memory/memory.hpp"
#include "memory/object.hpp"

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

		
		// todo: figure out good name for this
		// and make into typedef?
		size_t componentTypeId;

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




		static void UpdateAll();
		static void LateUpdateAll();
		static void OnGuiAll();

		



	};
}
