#include "physics/physics.hpp"

#include "engine.hpp"
#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"
#include "internal.hpp"

#include <glm/trigonometric.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

// Applies linear and angular forces to all RigidBodies
void ApplyForces() {

	for (RigidBody* rb : RigidBody::instances) {

		Transform* t = rb->gameObject->GetComponent<Transform>();

		if (rb->isAffectedByGravity)
			rb->AddImpulse(Physics::gravity / rb->mass);

		vec3 forces = rb->forces + rb->linearImpulse;
		vec3 torque = rb->torques + rb->angularImpulse;

		vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime;
		rb->linearVelocity *= clamp(1.0f - rb->linearDrag * Time::deltaTime, 0.0f, 1.0f);
		t->position += rb->linearVelocity * Time::deltaTime;

		vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		rb->angularVelocity *= clamp(1.0f - rb->angularDrag * Time::deltaTime, 0.0f, 1.0f);
		t->rotation += degrees(rb->angularVelocity) * Time::deltaTime;

		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };
	}
}

// Detects collisions between colliders, and later calls OnCollisionEnter for those who collided
void HandleCollisions() {

	vector<Collider*>& colliders = Collider::instances;

	// todo: replace per instance overlapping colliders vector with 
	// static vector here, so in case deleted game objects dont get out of sync

	if (colliders.size() <= 1) return;


	// find all new collisions, and call OnCollisionEnter
	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];

			bool wasAlreadyOverlapping = false;
			for (auto* c : ca->overlappingColliders){
				if (c == cb) {
					wasAlreadyOverlapping = true;
					break;
				}
			}

			bool isOverlapping = ca->OverlapsWith(cb);

			if (isOverlapping){
				if (!wasAlreadyOverlapping) {
					ca->overlappingColliders.push_back(cb);
					cb->overlappingColliders.push_back(ca);
					for (auto* c : ca->gameObject->components) c->OnCollisionEnter(cb->gameObject);
					for (auto* c : cb->gameObject->components) c->OnCollisionEnter(ca->gameObject);
				}
				for (auto* c : ca->gameObject->components) c->OnCollisionStay(cb->gameObject);
				for (auto* c : cb->gameObject->components) c->OnCollisionStay(ca->gameObject);
			}
			else {
				if (wasAlreadyOverlapping) {
					for (auto* c : ca->gameObject->components) c->OnCollisionExit(cb->gameObject);
					for (auto* c : cb->gameObject->components) c->OnCollisionExit(ca->gameObject);

					for (size_t i = 0; i < ca->overlappingColliders.size(); i++) {
						if (cb == ca->overlappingColliders[i]) {
							ca->overlappingColliders.erase(ca->overlappingColliders.begin() + i);
							break;
						}
					}
					for (size_t i = 0; i < cb->overlappingColliders.size(); i++) {
						if (ca == cb->overlappingColliders[i]) {
							cb->overlappingColliders.erase(cb->overlappingColliders.begin() + i);
							break;
						}
					}
				}
			}
		}



	}


}

vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

void PhysicsUpdate() {
	ApplyForces();
	HandleCollisions();
}


