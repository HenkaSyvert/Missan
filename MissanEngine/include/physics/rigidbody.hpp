#pragma once

#include "component.hpp"

#include <glm/vec3.hpp>

namespace Missan {

	///
	/// Class for GameObjects that are affected by physics
	class RigidBody : public Component<RigidBody> {

	public:

		/// 
		/// The mass (kg) of this RigidBody
		float mass = 1.0f;

		/// 
		/// The linear velocity (m/s) of this RigidBody
		glm::vec3 linearVelocity = { 0,0,0 };



		/// 
		/// The angular force required to rotate this RigidBody
		glm::vec3 inertiaTensor = { 0,0,0 };

		/// 
		/// The angular velocity (rad/s) of this RigidBody
		glm::vec3 angularVelocity = { 0,0,0 };



		/// 
		/// Sum of all linear forces currently acting on this RigidBody
		glm::vec3 forces = { 0,0,0 };

		/// 
		/// Sum of all torques currently acting on this RigidBody
		glm::vec3 torques = { 0,0,0 };

		/// 
		/// is this RigidBody affected by gravity?
		bool isAffectedByGravity = true;



		/// 
		/// Linear impulse that will be applied this frame
		glm::vec3 linearImpulse = { 0,0,0 };

		/// 
		/// angular impulse that will be applied this frame
		glm::vec3 angularImpulse = { 0,0,0 };

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



		void DisplayInInspector();

		void Start();
	};
}