#pragma once
#include "physics/rigidbody.hpp"
#include "physics/collider.hpp"
#include "transform.hpp"
#include "component.hpp"

#include <glm/vec3.hpp>

#include <vector>

namespace Missan {

	class ContactPoint {

	public:
		
		// the face normal at the point of contact
		glm::vec3 normal;
		
		glm::vec3 point;
		
		// the amount of separation between the two colliders. 
		// negative means overlap i.e. collision. 
		float separation;

	};

	class Collision {

	public:

		Transform* thisTransform = nullptr;
		RigidBody* thisRigidbody = nullptr;
		Collider* thisCollider = nullptr;

		Transform* otherTransform = nullptr;
		RigidBody* otherRigidbody = nullptr;
		Collider* otherCollider = nullptr;

		glm::vec3 relativeVelocity;
		glm::vec3 impulse;

		std::vector<ContactPoint> contactPoints;

		// the same collision but flipped perspective of ours/other components, 
		// for passing into OnCollisionsXXX correctly. 
		Collision FlipOtherThis() {
			Collision collision(*this);
			
			collision.thisTransform = otherTransform;
			collision.thisCollider  = otherCollider;
			collision.thisRigidbody = otherRigidbody;

			collision.otherTransform = thisTransform;
			collision.otherCollider  = thisCollider;
			collision.otherRigidbody = thisRigidbody;

			return collision;
		}

	};


}