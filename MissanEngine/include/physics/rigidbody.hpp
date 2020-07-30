#pragma once

#include "missanpch.hpp"
#include "core/component.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "core/time.hpp"

namespace Missan {

	class RigidBody : public Component {

	public:

		// The mass (kg) of this RigidBody
		float mass = 1.0f;

		// The force (N) acting on this RigidBody
		glm::vec3 force = { 0,0,0 };

		// The velocity (m/s) of this RigidBody
		glm::vec3 velocity = { 0,0,0 };

		
		// The angular force (rad/s) required to rotate this RigidBody
		glm::vec3 inertiaTensor;

		// The angular forces acting on this RigidBody
		glm::vec3 torque;

		// The angular velocity of this RigidBody
		glm::vec3 angularVelocity;


		// 
		glm::vec3 centerOfMass = { 0,0,0 };



		// NOT PART OF PUBLIC API ////////////////////////

		void Start();
		
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}