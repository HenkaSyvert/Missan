#include "physics/physics.hpp"

#include "core/engine.hpp"
#include "core/gameobject.hpp"
#include "core/time.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"
#include "physics/boundingbox.hpp"

using namespace Missan;


// PRIVATE



// Applies linear and angular forces to all RigidBodies
void ApplyForces(std::vector<RigidBody*>& rbs) {

	for (RigidBody* rb : rbs) {

		Transform* t = rb->GetGameObject().GetComponent<Transform>();

		glm::vec3 forces = rb->forces + rb->linearImpulse;
		glm::vec3 torque = rb->torques + rb->angularImpulse;


		glm::vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime;
		t->position += rb->linearVelocity * Time::deltaTime;


		glm::vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		t->rotationDeg += glm::degrees(rb->angularVelocity) * Time::deltaTime;


		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };

	}


}

// Detects collisions between colliders, and later calls OnCollisionEnter for those who collided
std::vector<std::pair<GameObject*, GameObject*>> DetectCollisions(std::vector<Collider*>& colliders) {

	std::vector<std::pair<GameObject*, GameObject*>> collisions;

	if (colliders.empty()) return collisions;

	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];
		Transform* ta = ca->GetGameObject().GetComponent<Transform>();
		RigidBody* rba = ca->GetGameObject().GetComponent<RigidBody>();

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];
			Transform* tb = cb->GetGameObject().GetComponent<Transform>();
			RigidBody* rbb = cb->GetGameObject().GetComponent<RigidBody>();

			glm::vec3 overlap = ca->OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (glm::length(overlap) < tolerance){
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




// PUBLIC

glm::vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };


void Physics::Update() {
	
	auto gos = Engine::GetActiveScene()->gameObjects;

	// get all RigidBodies
	std::vector<RigidBody*> rbs;
	for (auto* g : gos)
		if (g->GetComponent<RigidBody>() != nullptr)
			rbs.push_back(g->GetComponent<RigidBody>());

	// get all Colliders
	std::vector<Collider*> cs;
	for (auto* g : gos)
		if (g->GetComponent<Collider>() != nullptr)
			cs.push_back(g->GetComponent<Collider>());



	ApplyForces(rbs);

	// Send OnCollisionEnter messages..
	for (std::pair<GameObject*, GameObject*>& collision : DetectCollisions(cs)) {
		for (Component* c : collision.first->components) {
			c->OnCollisionEnter(collision.second);
		}
	}


}


