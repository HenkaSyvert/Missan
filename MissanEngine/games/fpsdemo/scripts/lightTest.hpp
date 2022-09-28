#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace glm;

class LightTest : public Component {

public:
	Material* m;


	void OnGUI() {
		Light* l = Light::light;


		ImGui::SliderFloat3("material.ambient", (float*)&m->ambient, 0, 1);
		ImGui::SliderFloat3("material.diffuse", (float*)&m->diffuse, 0, 1);
		ImGui::SliderFloat3("material.specular", (float*)&m->specular, 0, 1);
		ImGui::SliderFloat("material.shininess", &m->shininess, 0, 100);

		ImGui::SliderFloat3("light.ambient", (float*)&m->ambient, 0, 1);
		ImGui::SliderFloat3("light.diffuse", (float*)&m->diffuse, 0, 1);
		ImGui::SliderFloat3("light.speculare", (float*)&m->specular, 0, 1);
	
	}



	LightTest* Clone() const {
		return new LightTest(*this);
	}
};