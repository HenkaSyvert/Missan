#pragma once

#include "missan.hpp"
#include "projectile.hpp"
#include "globals.hpp"

using namespace Missan;
using namespace glm;

class Weapon : public Component {

public:

	// The projectile this weapon fires
	GameObject* projectile = nullptr;

	// the force, in newtons, with which projectiles will be launched
	float force = 50.f;


	// distance from player from which projectiles spawn
	float muzzleDistance = 1.1f;

	// minimum delay between each projectile
	float delay = 0.2f;



private:
	// time when last projectile was fired
	float timeStamp = 0;

	// can weapon fire?
	bool canFire = true;


	void SpawnProjectile() {
		GameObject* p = GameObject::Instantiate(*projectile);
		Transform* t = gameObject->GetComponent<Transform>();
		Transform* pTrans = p->GetComponent<Transform>();
		RigidBody* prb = p->GetComponent<RigidBody>();
		prb->mass = 10.0f;

		pTrans->position = t->position + t->forward * muzzleDistance;
		pTrans->rotation = t->rotation;

		prb->AddImpulse(t->forward * force, { 0, .5, 0 }, false);
	}

public:
	void Start() {

		// make prefab for projectile...
		projectile = new GameObject();
		projectile->AddComponent<Transform>();
		auto* rend = projectile->AddComponent<Renderer>();
		rend->mesh = Resources::GetMesh("resources/meshes/cube.mesh");
		rend->texture = Resources::GetTexture("resources/textures/cat.png");
		projectile->AddComponent<Collider>();
		projectile->AddComponent<RigidBody>();
		projectile->AddComponent<Projectile>();
		projectile->GetComponent<Transform>()->scale = { .1,.1,.1 };

		timeStamp = Time::time;
	}

	void Update() {

		if (isPaused) return;

		if (!canFire) {
			if (Time::time - timeStamp > delay) {
				canFire = true;
			}
			else return;
		}
		else if (Input::GetMouseButtonDown(MouseButton::Left)) {
			SpawnProjectile();
			canFire = false;
			timeStamp = Time::time;

		}

	}


	Weapon* Clone() const { return new Weapon(*this); }

};
