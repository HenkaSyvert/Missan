#pragma once

#include "missan.hpp"

using namespace Missan;

class Projectile : public Component {

public:

	// how long, in seconds, this projectile will live
	float lifespan = 1.0f;

	// how much damage this projectile inflicts
	float damage = 1.5f;

	bool isAlive = true;


	void Start() {
		startTime = Time::time;
	}

	void Update() {
		if (!isAlive) return;
		if (Time::time - startTime > lifespan) {
			Engine::Destroy(&GetGameObject());
			std::cout << "projectile is dead\n";
			isAlive = false;
		}
	}

private:
	float startTime;



	Projectile* Clone() const { return new Projectile(*this); }
};