#include "physics.hpp"

#include "core/engine.hpp"
#include "components/collider.hpp"
#include "rigidbody.hpp"
#include "components/transform.hpp"
#include "gameobject.hpp"

#include "components/collider.hpp"
#include "components/transform.hpp"
#include "rigidbody.hpp"

using namespace missan;



// PUBLIC


glm::vec3 Physics::gravity = { 0.0f, -9.82f, 0.0f };

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
		for (auto* cb : cs) {
			if (ca == cb) continue;		// ignore our own Collider

			auto displacement = ca->OverlapsWith(cb);
			if (displacement != glm::vec3(0,0,0)) {
				auto* ta = ca->GetGameObject().GetComponent<Transform>();

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

	/*
	for (int i = 0; i < gos.size() - 1; i++) {
		auto* a = gos[i];
		Collider* ca = a->GetComponent<Collider>();
		if (ca == nullptr) continue;

		for (int j = i + 1; j < gos.size(); j++) {
			auto* b = gos[j];
			Collider* cb = b->GetComponent<Collider>();
			if (cb == nullptr) continue;

			float overlap = ca->OverlapsWith(cb);
			if (overlap != 0) {
				glm::vec3 aCenter = a->GetComponent<Transform>()->position;
				glm::vec3 bCenter = b->GetComponent<Transform>()->position;
				glm::vec3 displacementDirection(b - a);
				displacementDirection = glm::normalize(displacementDirection);

				RigidBody* ra = a->GetComponent<RigidBody>();
				RigidBody* rb = b->GetComponent<RigidBody>();

				std::cout << "collision!\n";

				if (ra == nullptr) {

					if (rb == nullptr) {
						// just colliders, send message
					}
					else {
						// displace b
						b->GetComponent<Transform>()->position -= displacementDirection * overlap;
					}

				}
				else {

					if (rb == nullptr) {
						// displace a
						a->GetComponent<Transform>()->position += displacementDirection * overlap;
					}
					else {
						// displace both
						a->GetComponent<Transform>()->position += displacementDirection * (overlap / 2);
						b->GetComponent<Transform>()->position -= displacementDirection * (overlap / 2);
					}

				}




			}

		}
	}
	*/
	

}



