#pragma once
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

		class RigidBody* otherRigidBody = nullptr;
		class Collider* otherCollider = nullptr;
		class GameObject* other = nullptr;

		glm::vec3 relativeVelocity;

		// the sum of the forces required to resolve the penetration, as per the contact points
		glm::vec3 impulse;
		
		// one contact point per axis that overlaps. 
		std::vector<ContactPoint> contactPoints;

	};


}