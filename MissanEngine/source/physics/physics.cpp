#include "physics/physics.hpp"

#include "core/engine.hpp"
#include "core/gameobject.hpp"
#include "core/time.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"

using namespace Missan;


// PRIVATE

// Applies linear and angular forces to all RigidBodies
void ApplyForces(std::vector<Collider*>& cs, std::vector<RigidBody*>& rbs) {

	for (auto* rb : rbs) {

		auto* c = rb->GetGameObject().GetComponent<Collider>();
		auto* t = rb->GetGameObject().GetComponent<Transform>();

		// gravitational force
		rb->force = rb->mass * Physics::gravity;

		// additional forces
		glm::vec3 f(0, .1, 0);

		// where we apply f, measured as offset from center of mass.
		// this can even be outside the shape of the RigidBody, as
		// if we're applying some kind of extended arm moment
		glm::vec3 pointOfApplication(10, 0, 0);

		// note that gravity's point of application is always the 
		// center of mass, which yields no angular momentum

		// the resulting torque from f applied at pointOfApplication
		rb->torque = glm::cross(pointOfApplication, rb->force);


		glm::vec3 linearAcceleration = rb->force / rb->mass;
		rb->velocity += linearAcceleration * Time::deltaTime;
		t->position += rb->velocity * Time::deltaTime;

		glm::vec3 angularAcceleration(rb->torque / rb->inertiaTensor);
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		t->rotationDeg += glm::degrees(rb->angularVelocity) * Time::deltaTime;

	}


}

void UpdatePositionsAndVelocities(std::vector<Collider*>& cs, std::vector<RigidBody*>& rbs) {

}

void DetectCollisions(std::vector<Collider*>& cs, std::vector<RigidBody*>& rbs) {

}

void SolveConstraints(std::vector<Collider*>& cs, std::vector<RigidBody*>& rbs) {

}



// PUBLIC

glm::vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

// test
bool hasSlowed = false;

void Physics::Update() {
	
	if (!hasSlowed) Time::timeScale = 0.25;

	auto gos = Engine::GetActiveScene()->gameObjects;

	// get all RigidBodies
	std::vector<RigidBody*> rbs;
	for (auto* g : gos)
		if (g->GetComponent<RigidBody>() != nullptr)
			rbs.push_back(g->GetComponent<RigidBody>());
	if (rbs.size() == 0) return;	// no rigidbodies to simulate

	// get all Colliders
	std::vector<Collider*> cs;
	for (auto* g : gos)
		if (g->GetComponent<Collider>() != nullptr)
			cs.push_back(g->GetComponent<Collider>());

	ApplyForces(cs, rbs);

	/*
	for (int i = 0; i < rbs.size(); i++) {
		auto* rba = rbs[i];
		auto* ca = rba->GetGameObject().GetComponent<Collider>();
		auto* ta = ca->GetGameObject().GetComponent<Transform>();

		

		// attempt to do normal force thingy
		auto gravitationalForce = Physics::gravity * rba->mass;
		auto deltaVelocity = gravitationalForce * Time::deltaTime;



		for (auto* cb : cs) {
			if (ca == cb) continue;		// ignore our own Collider

			auto displacement = ca->OverlapsWith(cb);
			if (displacement != glm::vec3(0,0,0)) {
				

				auto* rbb = cb->GetGameObject().GetComponent<RigidBody>();
				if (rbb != nullptr) {
					// 2 RigidBodies colliding, displace both

				}
				else {
					// RigidBody colliding with Collider, only displace RigidBody
					ta->position -= displacement;
					
					

					std::cout << "collision\n";

				}

			}
		}
	}

	*/

}


