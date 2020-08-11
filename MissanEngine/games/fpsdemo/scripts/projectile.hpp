#pragma once

#include "missan.hpp"

using namespace Missan;

class Projectile : public Component {

public:

	// how long, in seconds, this projectile will live
	float lifespan = 3.0f;

	// how much damage this projectile inflicts
	float damage = 1.5f;


	void Start() {
		startTime = Time::time;
	}

	void Update() {
		if (Time::time - startTime > lifespan) {
			Engine::Destroy(&GetGameObject());
		}
	}

private:
	float startTime;



	Projectile* Clone() const { return new Projectile(*this); }
};