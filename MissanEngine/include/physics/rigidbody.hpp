#pragma once

#include "missanpch.hpp"
#include "core/component.hpp"
#include "core/transform.hpp"
#include "core/time.hpp"
#include "physics/collider.hpp"
#include "physics/physics.hpp"

namespace Missan {

	class RigidBody : public Component {

	public:

		// The mass (kg) of this RigidBody
		float mass = 1.0f;

		// The linear velocity (m/s) of this RigidBody
		glm::vec3 linearVelocity = { 0,0,0 };

		// How fast the rigidbody slows down (m/s)
		float linearDrag = 0.0f;



		// The angular force required to rotate this RigidBody
		glm::vec3 inertiaTensor = { 0,0,0 };

		// The angular velocity (rad/s) of this RigidBody
		glm::vec3 angularVelocity = { 0,0,0 };

		// How fast angular velocity slows down (rad/s)
		float angularDrag = 10.0f;



		// Sum of all linear forces currently acting on this RigidBody
		glm::vec3 forces = { 0,0,0 };

		// Sum of all torques currently acting on this RigidBody
		glm::vec3 torques = { 0,0,0 };

		// is this RigidBody affected by gravity?
		bool isAffectedByGravity = true;



		// Linear impulse that will be applied this frame
		glm::vec3 linearImpulse = { 0,0,0 };

		// angular impulse that will be applied this frame
		glm::vec3 angularImpulse = { 0,0,0 };



		// Applies force to the RigidBody at point, using world coordinates unless specified otherwise.
		// Force applied anywhere but center of mass (i.e. {0,0,0} ) will generate torque.
		// Force, unlike an impulse, is applied continuously once added, e.g. gravity is only added once
		// but affects the RigidBody each frame
		void AddForce(glm::vec3 newForce, glm::vec3 point = { 0,0,0 }, bool useLocalSpace = false) {
			if (useLocalSpace) {
				auto* t = GetGameObject().GetComponent<Transform>();
				newForce = t->TransformPoint(newForce);
				point = t->TransformPoint(point);
			}		
			forces += newForce;
			torques += glm::cross(point, newForce);
		}

		// Applies an impulse to the RigidBody at point, using world coordinates unless specified otherwise.
		// Impulse applied anywhere but center of mass (i.e. {0,0,0} ) will generate torque.
		// Impulse, unlike force, is only applied once
		void AddImpulse(glm::vec3 impulse, glm::vec3 point = { 0,0,0 }, bool useLocalSpace = false) {
			if (useLocalSpace) {
				auto* t = GetGameObject().GetComponent<Transform>();
				impulse = t->TransformPoint(impulse);
				point = t->TransformPoint(point);
			}
			linearImpulse += impulse;
			angularImpulse += glm::cross(point, impulse);
		}



		// NOT PART OF PUBLIC API ////////////////////////

		void Start();
		
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}