#pragma once

#include "missan.hpp"
#include <iostream>

using namespace Missan;
using namespace std;

class ColorTest : public Component {
public:
		


	void OnGUI() {
		glm::vec4* c = &gameObject->GetComponent<Renderer>()->material->color;

		ImGui::SliderFloat("r", &c->r, 0, 1);
		ImGui::SliderFloat("g", &c->g, 0, 1);
		ImGui::SliderFloat("b", &c->b, 0, 1);
		ImGui::SliderFloat("a", &c->a, 0, 1);
	}



	ColorTest* Clone() const {
		return new ColorTest(*this);
	}
};