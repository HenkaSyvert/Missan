#pragma once

#include "missan.hpp"

using namespace Missan;

class Weapon : public Component {

public:

	// The projectile this weapon fires
	GameObject* projectile = nullptr;

	// the force, in newtons, with which projectiles will be launched
	float force = 100.f;




	void Start() {
		projectile = new GameObject();
		projectile->AddComponent<
	}



	Weapon* Clone() const { return new Weapon(*this); }

};
