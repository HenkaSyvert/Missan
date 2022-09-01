#include "physics.hpp"

#include "engine.hpp"
#include "gameobject.hpp"
#include "transform.hpp"
#include "collider.hpp"
#include "rigidbody.hpp"
#include "boundingbox.hpp"
#include "internal.hpp"

#include <glm/trigonometric.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

// Applies linear and angular forces to all RigidBodies
void ApplyForces() {

	auto& gos = EcsGetGameObjects();

	// get all RigidBodies
	vector<RigidBody*> rbs;
	for (auto* g : gos)
		if (g->GetComponent<RigidBody>() != nullptr)
			rbs.push_back(g->GetComponent<RigidBody>());


	for (RigidBody* rb : rbs) {

		Transform* t = rb->gameObject->GetComponent<Transform>();

		if (rb->isAffectedByGravity)
			rb->AddImpulse(Physics::gravity / rb->mass);

		vec3 forces = rb->forces + rb->linearImpulse;
		vec3 torque = rb->torques + rb->angularImpulse;

		vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime;
		t->position += rb->linearVelocity * Time::deltaTime;

		vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		t->rotationDeg += degrees(rb->angularVelocity) * Time::deltaTime;

		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };
	}
}

// Detects collisions between colliders, and later calls OnCollisionEnter for those who collided
void HandleCollisions() {
	auto& gos = EcsGetGameObjects();

	// get all Colliders
	vector<Collider*> colliders;
	for (auto* g : gos)
		if (g->GetComponent<Collider>() != nullptr)
			colliders.push_back(g->GetComponent<Collider>());

	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];

			vec3 overlap = ca->OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (length(overlap) < tolerance) continue;
			else {
				for (auto* c : ca->gameObject->components) c->OnCollisionEnter(cb->gameObject);
				for (auto* c : cb->gameObject->components) c->OnCollisionEnter(ca->gameObject);
			}

		}
	}
}




vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };


void PhysicsUpdate() {
	ApplyForces();
	HandleCollisions();
}


