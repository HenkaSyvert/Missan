#pragma once
#include "physics/rigidbody.hpp"
#include "physics/collider.hpp"
#include "transform.hpp"
#include "component.hpp"

#include <glm/vec3.hpp>

namespace Missan {

	class Collision {

	public:

		Transform* ourTransform = nullptr;
		Transform* otherTransform = nullptr;

		RigidBody* ourRigidbody = nullptr;
		RigidBody* otherRigidbody = nullptr;

		Collider* ourCollider = nullptr;
		Collider* otherCollider = nullptr;

		glm::vec3 relativeVelocity;
		glm::vec3 impulse;

		glm::vec3 contactPoint;
		glm::vec3 contactNormal;
		float separation;


	};


}