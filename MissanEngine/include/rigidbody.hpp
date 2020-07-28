#pragma once

#include "components/component.hpp"

namespace missan {

	class RigidBody : public Component {

	public:


		// NOT PART OF PUBLIC API ////////////////////////
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}