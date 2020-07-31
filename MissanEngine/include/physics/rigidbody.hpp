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

		// The velocity (m/s) of this RigidBody
		glm::vec3 velocity = { 0,0,0 };

		// how much the velocity will slow down (think air resistance)
		float drag = 10.0f;


		// The angular force (rad/s) required to rotate this RigidBody
		glm::vec3 inertiaTensor = { 0,0,0 };

		// The angular velocity of this RigidBody
		glm::vec3 angularVelocity = { 0,0,0 };

		// How much angular velocity will decrease each second
		float angularDrag = 10.0f;



		// the new forces being applied this frame
		glm::vec3 newForces = { 0,0,0 };

		// the new torque being applied this frame
		glm::vec3 newTorque = { 0,0,0 };

		// is this RigidBody affected by gravity?
		bool isAffectedByGravity = true;

		// Applies force to the RigidBody at point, measured in local 
		void AddForce(glm::vec3 force, glm::vec3 point = { 0,0,0 }) {
			newForces += force;
			newTorque += glm::cross(point, force);
		}



		// NOT PART OF PUBLIC API ////////////////////////

		void Start();
		
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}