#include "physics/rigidbody.hpp"

#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "physics/physics.hpp"

using namespace Missan;

// PRIVATE

void RigidBody::Start() {
	auto* c = GetGameObject().GetComponent<Collider>();
	if (c == nullptr) {
		std::cout << "RigidBody requires Collider Component!\n";
		exit(EXIT_FAILURE);
	}

	if (isAffectedByGravity) {
		AddForce(Physics::gravity / mass);
	}

	// currently rigidbodies only work with box colliders
	auto s = c->boundingBox.size;
	inertiaTensor =  {s.y* s.y + s.z * s.z, s.x* s.x + s.z * s.z, s.x* s.x + s.y * s.y};
	inertiaTensor *= mass / 12.0f;

}


void RigidBody::AddForce(glm::vec3 newForce, glm::vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		auto* t = GetGameObject().GetComponent<Transform>();
		newForce = t->TransformPoint(newForce);
		point = t->TransformPoint(point);
	}
	forces += newForce;
	torques += glm::cross(point, newForce);
}

void RigidBody::AddImpulse(glm::vec3 impulse, glm::vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		auto* t = GetGameObject().GetComponent<Transform>();
		impulse = t->TransformPoint(impulse);
		point = t->TransformPoint(point);
	}
	linearImpulse += impulse;
	angularImpulse += glm::cross(point, impulse);
}

