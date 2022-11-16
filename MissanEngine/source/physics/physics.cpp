#include "physics/physics.hpp"

#include "engine.hpp"
#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"
#include "physics/collision.hpp"
#include "internal.hpp"


#include <glm/trigonometric.hpp>
#include <glm/glm.hpp>

#include <limits>
#include <vector>

using namespace Missan;
using namespace std;
using namespace glm;





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



vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

void PhysicsUpdate() {
	ApplyForces();
	DetectCollisions();
}


