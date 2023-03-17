#pragma once

#include "ecs.hpp"
#include "physics/collision.hpp"
#include "physics/collider.hpp"

#include <glm/vec3.hpp>

namespace Missan {

	///
	/// Class for GameObjects that are affected by physics. GameObjects with RigidBodies
	/// are automatically simulated by the physics engine. 
	class RigidBody : public Component<RigidBody> {

	public:

		/// 
		/// The mass (kg) of this RigidBody. 
		float mass = 1.0f;

		/// 
		/// The linear velocity (m/s) of this RigidBody. 
		glm::vec3 linearVelocity = { 0,0,0 };

		///
		/// The linear drag of this RigidBody. This simulates air (or other medium) resistance, 
		/// though only as an approximation, not according to the actual formulae. 
		float linearDrag = 1;

		/// 
		/// The angular force required to rotate this RigidBody. 
		/// It's basically the rotational equivalent of mass:
		/// higher values means more force required to rotate the body. 
		glm::vec3 inertiaTensor = { 0,0,0 };

		/// 
		/// The angular velocity (rad/s) of this RigidBody
		glm::vec3 angularVelocity = { 0,0,0 };

		///
		/// The angular drag of this RigidBody. This simulates air (or other medium) resistance, 
		/// though only as an approximation, not according to the actual formulae. 
		float angularDrag = 1;

		/// 
		/// Sum of all linear forces currently acting on this RigidBody
		glm::vec3 forces = { 0,0,0 };

		/// 
		/// Sum of all torques currently acting on this RigidBody
		glm::vec3 torques = { 0,0,0 };

		/// 
		/// is this RigidBody affected by gravity?
		bool isAffectedByGravity = false;

		/// 
		/// Linear impulse that will be applied this frame
		glm::vec3 linearImpulse = { 0,0,0 };

		/// 
		/// angular impulse that will be applied this frame
		glm::vec3 angularImpulse = { 0,0,0 };

		///
		/// The Collider of this GameObject. 
		Collider* collider = nullptr;

		/// 
		/// Applies force to the RigidBody at point, using world coordinates unless specified otherwise.
		/// Force applied anywhere but center of mass (i.e. {0, 0, 0} ) will generate torque.
		/// Force, unlike an impulse, is applied continuously once added, e.g. gravity is only added once
		/// but affects the RigidBody each frame
		void AddForce(glm::vec3 newForce, glm::vec3 point = { 0,0,0 }, bool useLocalSpace = false);

		/// 
		/// Applies an impulse to the RigidBody at point, using world coordinates unless specified otherwise.
		/// Impulse applied anywhere but center of mass (i.e. {0, 0, 0} ) will generate torque.
		/// Impulse, unlike force, is only applied once
		void AddImpulse(glm::vec3 impulse, glm::vec3 point = { 0,0,0 }, bool useLocalSpace = false);

		void OnCollisionEnter(Collision collision);
		void OnCollisionStay(Collision collision);

		void DisplayInInspector();

		void Start();

	};

}