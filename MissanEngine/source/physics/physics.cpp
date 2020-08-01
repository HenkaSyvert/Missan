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

// temp
int counter = 0;


glm::vec3 CalculateDrag(RigidBody* rb) {
	BoundingBox bb = rb->GetGameObject().GetComponent<Collider>()->boundingBox;
	
	
	float airDensity = 1.293f;
	float dragCoefficient = 1.05f;	// for a cube
	float crossSectionArea = bb.size.x * bb.size.y;

	auto v = rb->linearVelocity;
	if (v == glm::vec3(0,0,0)) return glm::vec3(0, 0, 0);

	//std::cout << v.x << " " << v.y << " " << v.z << "\n";

	glm::vec3 dragForce = 0.5f * airDensity * dragCoefficient * crossSectionArea * v * v * -glm::normalize(v);

	//std::cout << dragForce.x << " " << dragForce.y << " " << dragForce.z << "\n";
	//std::cin.get();



	return dragForce;
}

float CalculateTerminalVelocity(RigidBody* rb) {
	BoundingBox bb = rb->GetGameObject().GetComponent<Collider>()->boundingBox;

	float airDensity = 1.293f;
	float dragCoefficient = 1.05f;	// for a cube
	float crossSectionArea = bb.size.x * bb.size.y;

	return sqrt(2 * rb->mass * glm::length(rb->forces) / airDensity * crossSectionArea * dragCoefficient);

}

// Applies linear and angular forces to all RigidBodies
void ApplyForces(std::vector<RigidBody*>& rbs) {

	for (auto* rb : rbs) {

		auto* t = rb->GetGameObject().GetComponent<Transform>();

		glm::vec3 forces = rb->forces + rb->linearImpulse;// +CalculateDrag(rb);
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


void DetectCollisions(std::vector<Collider*>& cs) {



}

void SolveConstraints(std::vector<Collider*>& cs, std::vector<RigidBody*>& rbs) {

}



// PUBLIC

glm::vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

// test
bool hasSlowed = false;

void Physics::Update() {
	
	if (!hasSlowed) Time::timeScale = 0.1f;

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
	//DetectCollisions(cs);

	
	for (int i = 0; i < rbs.size(); i++) {
		auto* rba = rbs[i];
		auto* ca = rba->GetGameObject().GetComponent<Collider>();
		auto* ta = ca->GetGameObject().GetComponent<Transform>();

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

					// temporary check to stop gravity: disable gravity if it it's something 
					// that's excerting a normal force mostly [-5%, +5%] vertical
					if (rba->isAffectedByGravity) {
						if (glm::dot(glm::normalize(displacement), glm::normalize(Physics::gravity * rba->mass)) < 0.05) {
							std::cout << "gravity disabled\n";
							rba->isAffectedByGravity = false;
							rba->linearVelocity.y = 0;
						}
					}

					std::cout << "collision\n";
				}
			}
		}
	}
	


}


