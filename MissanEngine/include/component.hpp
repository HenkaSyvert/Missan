#pragma once

#include "gameobject.hpp"
#include "clonable.hpp"

namespace Missan {

	class GameObject;

	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	/// Currently, derived classes MUST provide implementation of the Clone() method. 
	class Component : public IClonable {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		GameObject* gameObject = nullptr;

		///
		/// TODO: remove in future
		/// Must have definition - empty body - since derived classes will call it.
		inline virtual ~Component() { };

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
		/// Called during rendering
		inline virtual void OnRender() {}

		///
		/// Called during GUI rendering
		inline virtual void OnGUI() {}
		
		///
		/// Called prior to the GameObject being destroyed
		inline virtual void OnDestroy() {}

		///
		/// TODO: remove in future
		/// All derived classes of Component must provide an implementation of this method. 
		/// For class T inhereting from Component, it should look like this:
		/// T* Clone() const { return new T(*this); } 
		inline virtual Component* Clone() const = 0;	

	};

}
