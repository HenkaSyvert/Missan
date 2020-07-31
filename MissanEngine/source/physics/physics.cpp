#include "physics/physics.hpp"

#include "core/engine.hpp"
#include "core/gameobject.hpp"
#include "core/time.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"

using namespace Missan;


// PRIVATE

// difference of all points in a and b
std::vector<glm::vec3> CalcMinkowskiDifference(std::vector<glm::vec3>& a, std::vector<glm::vec3>& b) {
	std::vector<glm::vec3> diff;
	for (auto& pa : a) {
		for (auto& pb : b) {
			diff.push_back(pa - pb);
		}
	}
	return diff;
}

glm::vec3 CalcMinToOrigin(std::vector<glm::vec3>& ps) {
	float minDist = INFINITY;
	glm::vec3 v;
	for (auto& p : ps) {
		if (glm::length(p) < minDist) {
			minDist = glm::length(p);
			v = p;
		}
	}
	return v;
}

// Applies linear and angular forces to all RigidBodies
void ApplyForces(std::vector<RigidBody*>& rbs) {

	for (auto* rb : rbs) {

		auto* c = rb->GetGameObject().GetComponent<Collider>();
		auto* t = rb->GetGameObject().GetComponent<Transform>();

		// gravitational force
		if (rb->isAffectedByGravity)
			//rb->AddForce(Physics::gravity * rb->mass);

		
		rb->AddForce({ 0,10,0 }, { 1,0,0 });

		// actually these are impulses
		glm::vec3 linearAcceleration = rb->newForces / Time::deltaTime / rb->mass;
		rb->velocity += linearAcceleration * Time::deltaTime /(1.0f + rb->drag);
		t->position += rb->velocity * Time::deltaTime;

		glm::vec3 angularAcceleration = rb->newTorque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime / (1.0f + rb->angularDrag);
		t->rotationDeg += glm::degrees(rb->angularVelocity) * Time::deltaTime;

		rb->newForces = { 0,0,0 };
		rb->newTorque = { 0,0,0 };

	}


}


void DetectCollisions(std::vector<Collider*>& cs) {



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

	ApplyForces(rbs);
	DetectCollisions(cs);


}


