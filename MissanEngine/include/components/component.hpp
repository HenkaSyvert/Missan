#pragma once

#include "gameobject.hpp"
#include "interfaces/clonable.hpp"

namespace missan {

	// base class for all components

	class Component : public IClonable {

	private:
		class GameObject* gameObject_ptr = nullptr;
		
	public:
		// IClonable interface
		virtual ~Component() {};	// must have definition - empty body - since derived classes will call it
		virtual Component* Clone() const = 0;



		void AttachToGameObject(GameObject& gameObject) { gameObject_ptr = &gameObject; };
		class GameObject& gameObject = *gameObject_ptr;

		virtual void Update() = 0;

	};

}
