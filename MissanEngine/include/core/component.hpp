#pragma once

#include "core/gameobject.hpp"
#include "interfaces/clonable.hpp"
//#include "physics/collision.hpp"

namespace Missan {

	//// 
/// just a forward declaration
	class GameObject;

	//// 
/// Components define behavior of GameObjects. To make a custom script, inherit from Component.
	//// 
/// Currently, derived classes MUST provide implementation of the Clone() method. 
	class Component : public IClonable {
		
	public:

		//// 
/// Attaches this Component to gameObject
		inline void AttachToGameObject(GameObject& gameObject) { gameObject_ptr = &gameObject; };

		//// 
/// Returns the GameObject this Component is attached to
		inline class GameObject& GetGameObject() { return *gameObject_ptr; }


		
		/// 
/// EVENT FUNCTIONS, in order of execution. Override these in your own scripts

		/// 
/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		//// 
/// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(GameObject* other){}		

		//// 
/// Called every frame
		inline virtual void Update() {}

		//// 
/// Called every frame, after all regular Update events
		inline virtual void LateUpdate() {}

		//// 
/// Called during rendering, just used by Renderer Components atm
		inline virtual void OnRender() {}

		//// 
/// Called during GUI rendering
		inline virtual void OnGUI() {}
		
		//// 
/// Called prior to being destroyed
		inline virtual void OnDestroy() {}


		//// 
/// NOT PART OF PUBLIC API //////////////////////////////////

		//// 
/// Must have definition - empty body - since derived classes will call it
		inline virtual ~Component() {};

		//// 
/// All derived classes of Component must provide an implementation of this method. 
		//// 
/// For class T inhereting from Component, it should look like this:
		//// 
/// T* Clone() const { return new T(*this); } 
		inline virtual Component* Clone() const = 0;	



	private:
		GameObject* gameObject_ptr = nullptr;



	};

}
