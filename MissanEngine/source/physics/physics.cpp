#include "physics/physics.hpp"

#include "core/engine.hpp"
#include "core/gameobject.hpp"
#include "core/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"

using namespace Missan;

// PUBLIC

glm::vec3 Physics::gravity = { 0.0f, -0.1f, 0.0f };

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

	

}



