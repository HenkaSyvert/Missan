#pragma once

#include "gameobject.hpp"

namespace missan {

	class Component {
	private:
	public:
		class GameObject* gameObject_ptr = nullptr;

	
		virtual void Update() = 0;

	};

}
