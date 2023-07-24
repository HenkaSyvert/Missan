#pragma once

#include "ecs.hpp"
#include "collision.hpp"
#include "collider.hpp"

#include <glm/vec3.hpp>

namespace Missan {

	///
	/// Class for GameObjects that are affected by physics. GameObjects with RigidBodies
	/// are automatically simulated by the physics engine. 
	class RigidBody : public Component<RigidBody> {

	public:

		/// 
		/// The mass (kg) of this RigidBody. 
		float mass = 10.0f;

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
		/// Applies force to the RigidBody at point, using world coordinates.
		/// Force applied anywhere but center of mass (i.e. {0, 0, 0} ) will generate torque.
		/// Force, unlike an impulse, is applied continuously once added, e.g. gravity is only added once
		/// but affects the RigidBody each frame
		void AddForce(glm::vec3 newForce, glm::vec3 point = { 0,0,0 }) {
			forces += newForce;
			torques += cross(point, newForce);
		}

		/// 
		/// Applies an impulse to the RigidBody at point, using world coordinates.
		/// Impulse applied anywhere but center of mass (i.e. {0, 0, 0} ) will generate torque.
		void AddImpulse(glm::vec3 impulse, glm::vec3 point = { 0,0,0 }) {
			linearImpulse += impulse;
			angularImpulse += cross(point, impulse);
		}

		void DisplayInInspector() {
			using namespace ImGui;
			ShowDemoWindow();

			if (CollapsingHeader("Rigid Body")) {
				SliderFloat("Mass (kg)", &mass, .01f, 10000);
				DragFloat3("Linear Velocity", (float*)&linearVelocity);
				SliderFloat("Linear Drag", &linearDrag, 0, 1000);
				DragFloat3("Inertia Tensor", (float*)&inertiaTensor);
				DragFloat3("Angular Velocity", (float*)&angularVelocity);
				SliderFloat("Angular Drag", &angularDrag, 0, 1000);
				DragFloat3("forces", (float*)&forces);
				DragFloat3("Torques", (float*)&torques);
				Checkbox("use gravity", &isAffectedByGravity);
				DragFloat3("Linear Impulse", (float*)&linearImpulse);
				DragFloat3("Angular Impulse", (float*)&angularImpulse);

			}
		}

		void Start() {
			// currently rigidbodies only work with box colliders
			auto s = glm::vec3(1, 1, 1);
			inertiaTensor = { s.y * s.y + s.z * s.z,
							  s.x * s.x + s.z * s.z,
							  s.x * s.x + s.y * s.y };
			inertiaTensor *= mass / 12.0f;

			collider = GetComponent<Collider>();
		}

	};

}