#pragma once

#include "missanpch.hpp"
#include "core/component.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "core/time.hpp"

namespace Missan {

	class RigidBody : public Component {

	public:

		// The mass of this rigidbody, in kilograms
		float mass = 1.0f;

		// The forces acting on this RigidBody
		glm::vec3 forces = { 0,0,0 };

		// The velocity of this RigidBody
		glm::vec3 velocity = { 0,0,0 };



		// NOT PART OF PUBLIC API ////////////////////////

		void Start();
		
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}