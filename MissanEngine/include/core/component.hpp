#pragma once

#include "core/gameobject.hpp"
#include "interfaces/clonable.hpp"

namespace Missan {

	// just a forward declaration
	class GameObject;

	// Components define behavior of GameObjects. To make a custom script, inherit from Component
	class Component : public IClonable {
		
	public:

		// Attaches this Component to gameObject
		inline void AttachToGameObject(GameObject& gameObject) { gameObject_ptr = &gameObject; };

		// Returns the GameObject this Component is attached to
		inline class GameObject& GetGameObject() { return *gameObject_ptr; }


		
		// EVENT FUNCTIONS, in order of execution. Override these in your own scripts

		// Called only once for each GameObject
		virtual void Start() {}

		// Called when this Collider has begun touching another Collider
		//virtual void OnCollisionEnter(){}		// not implemented yet

		// Called every frame
		virtual void Update() {}

		// Called every frame, after all regular Update events
		virtual void LateUpdate() {}

		// Called during rendering, just used by Renderer Components atm
		virtual void OnRender() {}

		// Called during GUI rendering
		virtual void OnGUI() {}
		


		// NOT PART OF PUBLIC API //////////////////////////////////
		// must have definition - empty body - since derived classes will call it
		virtual ~Component() {};	
		virtual Component* Clone() const = 0;

	private:
		GameObject* gameObject_ptr = nullptr;

	};

}
