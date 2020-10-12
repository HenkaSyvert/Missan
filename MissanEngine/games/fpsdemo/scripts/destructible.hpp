#pragma once

#include "missan.hpp"
#include "projectile.hpp"

using namespace Missan;

// Script for destructible object
class Destructible : public Component {

public:

	int hp = 3;



	void TakeHit() {
		hp--;
		if (hp == 0) Engine::Destroy(&GetGameObject());
	}

	void Update() {
		GetGameObject().GetComponent<Transform>()->rotationDeg += glm::vec3(1, 1, 0);
	}

	void OnCollisionEnter(GameObject* other) {
		if (other->GetComponent<Projectile>() != nullptr) TakeHit();	
	}



	Destructible* Clone() const { 
		return new Destructible(*this); 
	}
};