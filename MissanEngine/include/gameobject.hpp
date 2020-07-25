#pragma once

#include <vector>
#include <typeinfo>

#include "components/component.hpp"

namespace missan {

	class GameObject {

	public:
		GameObject();
		~GameObject();
		GameObject(GameObject& copy);
		
		template <class T> T* AddComponent() {
			components.push_back(new T());
			components.back()->AttachToGameObject(*this);
			return (T*)components.back();
		}	
		template <class T> T* GetComponent() {
			for (Component* c : components)
				if (typeid(T) == typeid(*c))
					return (T*)c;
			return nullptr;
		}

		// used interally, not part of public API
		std::vector<class Component*> components;

	};

}