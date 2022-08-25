#pragma once

#include "missan.hpp"

using namespace Missan;

class Projectile : public Component {

public:

	// how long, in seconds, this projectile will live
	float lifespan = 3.0f;



	void Start() {
		startTime = Time::time;
	}

	void Update() {
		if (Time::time - startTime > lifespan) {
			GameObject::Destroy(&GetGameObject());
		}
	}

	void OnCollisionEnter(GameObject* other) {
		if (other->GetComponent<Collider>() != nullptr)
			GameObject::Destroy(&GetGameObject());
	}

private:
	float startTime = 0;



	Projectile* Clone() const { return new Projectile(*this); }
};