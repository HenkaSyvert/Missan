#pragma once

#include "missan.hpp"
#include "projectile.hpp"

using namespace Missan;

class Weapon : public Component {

public:

	// The projectile this weapon fires
	GameObject* projectile = nullptr;

	// the force, in newtons, with which projectiles will be launched
	float force = 100.f;

	// Key which fires weapon
	int fireKey = GLFW_KEY_F;

	// distance from player from which projectiles spawn
	float muzzleDistance = 0.2f;

	// minimum delay between each projectile
	float delay = 0.2f;


private:
	// time when last projectile was fired
	float timeStamp;

	// can weapon fire?
	bool canFire = true;


	void SpawnProjectile() {
		GameObject* p = Engine::Instantiate(*projectile);
		Transform* ourTrans = GetGameObject().GetComponent<Transform>();
		Transform* pTrans = p->GetComponent<Transform>();
		RigidBody* prb = p->GetComponent<RigidBody>();
		glm::vec3 forward = -ourTrans->GetBackwardVector();


		pTrans->position = ourTrans->position + forward * muzzleDistance;
		pTrans->rotationDeg = ourTrans->rotationDeg;

		prb->AddImpulse(forward * force);
	}

public:
	void Start() {
		projectile = new GameObject();
		auto* rend = projectile->AddComponent<Renderer>();
		rend->mesh_ptr = Resources::GetMesh("unitCube");
		rend->texture_ptr = Resources::GetTexture("cat.png");
		projectile->AddComponent<Collider>();
		projectile->AddComponent<RigidBody>();
		projectile->AddComponent<Projectile>();
		projectile->GetComponent<Transform>()->scale = { .1,.1,.1 };

		timeStamp = Time::time;
	}

	void Update() {

		if (!canFire) {
			if (Time::time - timeStamp > delay) {
				canFire = true;
			}
			else return;
		}
		else if (Input::IsKeyPressed(fireKey)) {
			SpawnProjectile();
			canFire = false;
			timeStamp = Time::time;

		}

	}


	Weapon* Clone() const { return new Weapon(*this); }

};
