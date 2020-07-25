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
		inline class GameObject& GetGameObject() { return *gameObject_ptr; }

		virtual void Start() {}
		virtual void Update() {}
		virtual void LateUpdate() {}
		virtual void OnGUI(){}
		virtual void OnRender(){}

	};

}
