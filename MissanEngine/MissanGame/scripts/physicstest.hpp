#pragma once

#include "core/component.hpp"
#include "physics/rigidbody.hpp"

using namespace Missan;

class PhysicsTest : public Component {

public:

	RigidBody* rb;

	void Start() {
		rb = GetGameObject().GetComponent<RigidBody>();

		rb->AddImpulse({ 0,10,0 }, { 1,0,0 });
	}





	PhysicsTest* Clone() const { return new PhysicsTest(*this); };

};