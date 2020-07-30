#include "physics/rigidbody.hpp"

using namespace Missan;

// PRIVATE

void RigidBody::Start() {
	auto* c = GetGameObject().GetComponent<Collider>();
	if (c == nullptr)
		std::cout << "RigidBody requires Collider Component!\n";

	// currently rigidbodies only work with box colliders
	auto s = c->boundingBox.size;
	inertiaTensor =  {s.y* s.y + s.z * s.z, s.x* s.x + s.z * s.z, s.x* s.x + s.y * s.y};
	inertiaTensor *= mass / 12.0f;

}

