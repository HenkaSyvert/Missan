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



		// NOT PART OF PUBLIC API //////////////////////////////////
		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnGUI(){}
		virtual void OnRender(){}
		
		// must have definition - empty body - since derived classes will call it
		virtual ~Component() {};	
		virtual Component* Clone() const = 0;

	private:
		GameObject* gameObject_ptr = nullptr;

	};

}
