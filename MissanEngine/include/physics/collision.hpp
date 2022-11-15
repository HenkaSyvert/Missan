#pragma once
#include "physics/rigidbody.hpp"
#include "physics/collider.hpp"
#include "transform.hpp"
#include "ecs.hpp"

#include <glm/vec3.hpp>

#include <vector>

namespace Missan {

	class ContactPoint {

	public:

		glm::vec3 normal;		
		glm::vec3 point;
		float separation;

	};

	class Collision {

	public:

		RigidBody* otherRigidBody = nullptr;
		Collider* otherCollider = nullptr;
		GameObject* other = nullptr;

		glm::vec3 relativeVelocity;

		// the sum of the forces required to resolve the penetration, as per the contact points
		glm::vec3 impulse;
		
		// one contact point per axis that overlaps. 
		std::vector<ContactPoint> contactPoints;

	};


}