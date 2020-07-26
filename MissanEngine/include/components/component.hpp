#pragma once

#include "gameobject.hpp"
#include "interfaces/clonable.hpp"

namespace missan {

	// just a forward declaration
	class GameObject;

	// Components define behavior of GameObjects. To make a custom script, inherit from Component
	class Component : public IClonable {
		
	public:

		// Attaches this Component to gameObject
		inline void AttachToGameObject(GameObject& gameObject) { gameObject_ptr = &gameObject; };

		// Returns the GameObject this Component is attached to
		inline class GameObject& GetGameObject() { return *gameObject_ptr; }


		
		// Event Functions, in order of execution

		// Called only once
		virtual void Start() {}

		// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(){}

		// Called every frame
		virtual void Update() {}

		// Called every frame, after all regular Update events
		virtual void LateUpdate() {}

		// Called during rendering
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
