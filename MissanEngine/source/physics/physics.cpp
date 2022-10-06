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

	RigidBody* rbs = Component::GetRawArray<RigidBody>();
	if (!rbs) return;
	size_t rbsCount = Component::GetArray<RigidBody>()->count;


	// todo: here could be a good place to have some sort of signature to
	// only accept game objects with both rigidbody and transofmr, or smth
	

	for (size_t i = 0; i < rbsCount; i++) {

		RigidBody* rb = &rbs[i];

		Transform* t = Component::Get<Transform>(rb->gameObjectId);
		if (!t) continue;

		if (rb->isAffectedByGravity)
			rb->AddImpulse(Physics::gravity / rb->mass);

		vec3 forces = rb->forces + rb->linearImpulse;
		vec3 torque = rb->torques + rb->angularImpulse;

		vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime;
		t->position += rb->linearVelocity * Time::deltaTime;

		vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		t->rotation += degrees(rb->angularVelocity) * Time::deltaTime;

		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };
	}
}

// Detects collisions between colliders, and later calls OnCollisionEnter for those who collided
void HandleCollisions() {

	// get all Colliders
	Collider* colliders = Component::GetRawArray<Collider>();
	if (!colliders) return;
	size_t collidersCount = Component::GetArray<Collider>()->count;

	if (collidersCount <= 1) return;

	for (size_t i = 0; i < collidersCount - 1; i++) {
		Collider* ca = &colliders[i];

		for (unsigned int j = i + 1; j < collidersCount; j++) {
			Collider* cb = &colliders[j];

			vec3 overlap = ca->OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (length(overlap) < tolerance) continue;
			else {

				for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
					PackedAssociativeArray* componentArray = Component::GetArrayById(componentTypeId);
					((Component*)componentArray->GetByIndex(ca->gameObjectId))->OnCollisionEnter(cb->gameObjectId);
				}
				for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
					PackedAssociativeArray* componentArray = Component::GetArrayById(componentTypeId);
					((Component*)componentArray->GetByIndex(cb->gameObjectId))->OnCollisionEnter(ca->gameObjectId);
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


