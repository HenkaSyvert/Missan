#include "physics/physics.hpp"

#include "engine.hpp"
#include "ecs/gameobject.hpp"
#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"
#include "physics/boundingbox.hpp"
#include "internal.hpp"

#include <glm/trigonometric.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

// Applies linear and angular forces to all RigidBodies
void ApplyForces() {

	RawArray<RigidBody> rbs = Component::GetRawArray<RigidBody>();


	// todo: here could be a good place to have some sort of signature to
	// only accept game objects with both rigidbody and transofmr, or smth
	// or add check that rb requires transform

	for (size_t i = 0; i < rbs.count; i++) {

		RigidBody& rb = rbs[i];

		Transform* t = Component::Get<Transform>(rb.gameObjectId);
		if (!t) continue;

		if (rb.isAffectedByGravity)
			rb.AddImpulse(Physics::gravity / rb.mass);

		vec3 forces = rb.forces + rb.linearImpulse;
		vec3 torque = rb.torques + rb.angularImpulse;

		vec3 linearAcceleration = forces / Time::deltaTime / rb.mass;
		rb.linearVelocity += linearAcceleration * Time::deltaTime;
		t->position += rb.linearVelocity * Time::deltaTime;

		vec3 angularAcceleration = torque / Time::deltaTime / rb.inertiaTensor;
		rb.angularVelocity += angularAcceleration * Time::deltaTime;
		t->rotation += degrees(rb.angularVelocity) * Time::deltaTime;

		rb.linearImpulse = { 0,0,0 };
		rb.angularImpulse = { 0,0,0 };
	}
}

// Detects collisions between colliders, and later calls OnCollisionEnter for those who collided
void HandleCollisions() {

	RawArray<Collider> colliders = Component::GetRawArray<Collider>();
	if (colliders.count <= 1) return;

	for (size_t i = 0; i < colliders.count - 1; i++) {
		Collider& ca = colliders[i];

		for (size_t j = i + 1; j < colliders.count; j++) {
			Collider& cb = colliders[j];

			vec3 overlap = ca.OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (length(overlap) < tolerance) continue;
			else {

				// maybe some sort of queueing thing is more efficient than doing it immediately. 
				auto casComps = Component::GetAttachedComponents(ca.gameObjectId);
				for (size_t i = 0; i < casComps.count; i++)
					casComps[i]->OnCollisionEnter(cb.gameObjectId);

				auto cbsComps = Component::GetAttachedComponents(cb.gameObjectId);
				for (size_t i = 0; i < cbsComps.count; i++)
					cbsComps[i]->OnCollisionEnter(ca.gameObjectId);
				

			}
		}
	}
}

vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

void PhysicsUpdate() {
	ApplyForces();
	HandleCollisions();
}


