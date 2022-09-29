#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace glm;

class LightTest : public Component {

public:
	Material* m;


	void OnGUI() {
		Light* l = Light::light;


		ImGui::SliderFloat4("material.ambient", (float*)&m->ambient, 0, 1);
		ImGui::SliderFloat4("material.diffuse", (float*)&m->diffuse, 0, 1);
		ImGui::SliderFloat4("material.specular", (float*)&m->specular, 0, 1);
		ImGui::SliderFloat("material.shininess", &m->shininess, 0, 100);

		ImGui::SliderFloat4("light.ambient", (float*)&l->ambient, 0, 1);
		ImGui::SliderFloat4("light.diffuse", (float*)&l->diffuse, 0, 1);
		ImGui::SliderFloat4("light.speculare", (float*)&l->specular, 0, 1);
	
	}



	LightTest* Clone() const {
		return new LightTest(*this);
	}
};