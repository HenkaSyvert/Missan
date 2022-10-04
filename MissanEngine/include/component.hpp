#pragma once

#include "gameobject.hpp"
#include "inspectable.hpp"

#include <typeinfo>

namespace Missan {

	class GameObject;

	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class Component : public Inspectable {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		GameObject* gameObject = nullptr;

		inline size_t getTypeId() { return typeid(*this).hash_code(); }

		///
		/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(GameObject* other){}		

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

		inline virtual void DisplayInInspector(){}

	};

}
