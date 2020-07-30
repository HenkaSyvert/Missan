#include "physics/rigidbody.hpp"

using namespace Missan;

// PRIVATE

void RigidBody::Start() {
	if (GetGameObject().GetComponent<Collider>() == nullptr)
		std::cout << "RigidBody requires Collider Component!\n";
}

