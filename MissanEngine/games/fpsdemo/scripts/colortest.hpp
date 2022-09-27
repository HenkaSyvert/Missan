#pragma once

#include "missan.hpp"

using namespace Missan;

class ColorTest : public Component {
public:
		
	glm::vec4* c;

	void Start() {
		c = &gameObject->GetComponent<Renderer>()->material->color;
		*c = { 1,0,0,0 };
	}

	void Update() {

		auto* r = &c->r;
		float dir = .05f;
		

	}



	ColorTest* Clone() const {
		return new ColorTest(*this);
	}
};