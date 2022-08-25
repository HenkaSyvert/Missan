#include "physics.hpp"

#include "engine.hpp"
#include "gameobject.hpp"
#include "time.hpp"
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
void ApplyForces(vector<RigidBody*>& rbs) {

	for (RigidBody* rb : rbs) {

		Transform* t = rb->GetGameObject().GetComponent<Transform>();

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
vector<pair<GameObject*, GameObject*>> DetectCollisions(vector<Collider*>& colliders) {

	vector<pair<GameObject*, GameObject*>> collisions;

	if (colliders.empty()) return collisions;

	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];
		Transform* ta = ca->GetGameObject().GetComponent<Transform>();
		RigidBody* rba = ca->GetGameObject().GetComponent<RigidBody>();

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];
			Transform* tb = cb->GetGameObject().GetComponent<Transform>();
			RigidBody* rbb = cb->GetGameObject().GetComponent<RigidBody>();

			vec3 overlap = ca->OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (length(overlap) < tolerance){
				continue;
			}
			else {
				collisions.push_back({ &ca->GetGameObject(),  &cb->GetGameObject() });
				collisions.push_back({ &cb->GetGameObject(),  &ca->GetGameObject() });
			}

		}
	}
	
	return collisions;
}




vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };


void PhysicsUpdate(vector<GameObject*>& gos) {
	

	// get all RigidBodies
	vector<RigidBody*> rbs;
	for (auto* g : gos)
		if (g->GetComponent<RigidBody>() != nullptr)
			rbs.push_back(g->GetComponent<RigidBody>());

	// get all Colliders
	vector<Collider*> cs;
	for (auto* g : gos)
		if (g->GetComponent<Collider>() != nullptr)
			cs.push_back(g->GetComponent<Collider>());



	ApplyForces(rbs);

	// Send OnCollisionEnter messages..
	for (pair<GameObject*, GameObject*>& collision : DetectCollisions(cs)) {
		for (Component* c : collision.first->components) {
			c->OnCollisionEnter(collision.second);
		}
	}

}


