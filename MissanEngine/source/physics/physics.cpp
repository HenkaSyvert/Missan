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

static vector<pair<Collider*, Collider*>> collisions;

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
			int collisionIndex;
			for (size_t k = 0; k < collisions.size(); k++) {
				auto p = collisions[k];
				if (p.first == ca && p.second == cb || p.first == cb && p.second == ca) {
					wasAlreadyOverlapping = true;
					collisionIndex = k;
					break;
				}
			}

			float overlap = ca->OverlapsWith(cb);
			bool isOverlapping = overlap < 0;

			if (isOverlapping){
				if (!wasAlreadyOverlapping) {
					collisions.push_back({ ca, cb });
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

					collisions.erase(collisions.begin() + collisionIndex);
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


