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

// returns the point in vertices that has the highest dot product with axis
glm::vec3 GetSupportPoint(std::vector<glm::vec3> vertices, glm::vec3 axis) {
	float highest = -INFINITY;
	glm::vec3 supportPoint(0, 0, 0);
	for (auto& p : vertices) {
		float dot = glm::dot(p, axis);
		if (dot > highest) {
			highest = dot;
			supportPoint = p;
		}
	}
	return supportPoint;
}

glm::vec3 GetSupportPoint(Collider& c, glm::vec3 axis) {
	auto* t = c.GetGameObject().GetComponent<Transform>();
	auto bb = c.boundingBox;
	return GetSupportPoint(t->TransformPoints(bb.GetVertices()), t->TransformPoint(axis));
}

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
	glm::vec3 v(0, 0, 0);
	for (auto& p : ps) {
		if (glm::length(p) < minDist) {
			minDist = glm::length(p);
			v = p;
		}
	}
	return v;
}




// drag
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

		float drag = 10.0f;
		float tolerance = 0.1f;

		auto* t = rb->GetGameObject().GetComponent<Transform>();

		glm::vec3 forces = rb->forces + rb->linearImpulse;
		glm::vec3 torque = rb->torques + rb->angularImpulse;


		glm::vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime/drag;
		if (glm::length(rb->linearVelocity) < tolerance)
			rb->linearVelocity = { 0,0,0 };
		t->position += rb->linearVelocity * Time::deltaTime;

		glm::vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime/drag;
		if (glm::length(rb->angularVelocity) < tolerance)
			rb->angularVelocity = { 0,0,0 };
		t->rotationDeg += glm::degrees(rb->angularVelocity) * Time::deltaTime;

		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };

	}


}


void DetectCollisions(std::vector<Collider*>& colliders) {
	
	for (int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];
		Transform* ta = ca->GetGameObject().GetComponent<Transform>();
		RigidBody* rba = ca->GetGameObject().GetComponent<RigidBody>();

		for (int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];
			Transform* tb = cb->GetGameObject().GetComponent<Transform>();
			RigidBody* rbb = cb->GetGameObject().GetComponent<RigidBody>();

			//auto avs = ta->TransformPoints(ca->boundingBox.GetVertices());
			//auto bvs = tb->TransformPoints(cb->boundingBox.GetVertices());
			//
			//std::vector<glm::vec3> markowskiDiff = CalcMinkowskiDifference(avs, bvs);
			//glm::vec3 overlap = CalcMinToOrigin(markowskiDiff);

			glm::vec3 overlap = ca->OverlapsWith(cb);

			float tolerance = 0.0001f;
			if (glm::length(overlap) < tolerance){
				continue;
			}


			if (rba == nullptr) {

				if (rbb == nullptr) {
					// case: 2 colliders
					// but atm do nothing because they are static

				}
				else {
					// case: A is collider, B is rigidbody
					tb->position -= overlap;
					std::cout << "col\n";
				}

			}
			else {

				if (rbb == nullptr) {
					// case: A is rigidbody, B is collider
					ta->position += overlap;
					std::cout << "col\n";
				}
				else {
					// case: 2 rigidbodies
					tb->position -= overlap/2.0f;
					ta->position += overlap/2.0f;
					std::cout << "col\n";
				}
			}

		}
	}
	

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
	if (rbs.size() == 0) return;	// no rigidbodies to simulate

	// get all Colliders
	std::vector<Collider*> cs;
	for (auto* g : gos)
		if (g->GetComponent<Collider>() != nullptr)
			cs.push_back(g->GetComponent<Collider>());

	ApplyForces(rbs);
	DetectCollisions(cs);



}


