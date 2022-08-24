#pragma once

#include "missan.hpp"
#include "projectile.hpp"

using namespace Missan;
using namespace glm;

// Script for destructible object. Object rotates with given deltaRotation
class Destructible : public Component {

public:

	int hp = 3;
	vec3 deltaRotation = { 1, 1, 0 };


	void TakeHit() {
		hp--;
		if (hp == 0) Engine::Destroy(&GetGameObject());
	}

	void Update() {
		GetGameObject().GetComponent<Transform>()->rotationDeg += deltaRotation;
	}

	void OnCollisionEnter(GameObject* other) {
		if (other->GetComponent<Projectile>() != nullptr) TakeHit();	
	}



	Destructible* Clone() const { 
		return new Destructible(*this); 
	}
};