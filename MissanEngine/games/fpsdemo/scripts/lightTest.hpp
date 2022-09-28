#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace glm;

class LightTest : public Component {

public:
	Material* m;
	Light* l;


	void OnGUI() {
		

		ImGui::Text("material\nambient");
		ImGui::SliderFloat("r", &m->ambient.r, 0, 1);
		ImGui::SliderFloat("g", &m->ambient.g, 0, 1);
		ImGui::SliderFloat("b", &m->ambient.b, 0, 1);
		ImGui::SliderFloat("a", &m->ambient.a, 0, 1);

		ImGui::Text("diffuse");
		ImGui::SliderFloat("r", &m->diffuse.r, 0, 1);
		ImGui::SliderFloat("g", &m->diffuse.g, 0, 1);
		ImGui::SliderFloat("b", &m->diffuse.b, 0, 1);
		ImGui::SliderFloat("a", &m->diffuse.a, 0, 1);

		ImGui::Text("specular");
		ImGui::SliderFloat("r", &m->specular.r, 0, 1);
		ImGui::SliderFloat("g", &m->specular.g, 0, 1);
		ImGui::SliderFloat("b", &m->specular.b, 0, 1);
		ImGui::SliderFloat("a", &m->specular.a, 0, 1);

		ImGui::Text("light\nambient");
		ImGui::SliderFloat("r", &l->ambient.r, 0, 1);
		ImGui::SliderFloat("g", &l->ambient.g, 0, 1);
		ImGui::SliderFloat("b", &l->ambient.b, 0, 1);
		ImGui::SliderFloat("a", &l->ambient.a, 0, 1);

		ImGui::Text("diffuse");
		ImGui::SliderFloat("r", &l->diffuse.r, 0, 1);
		ImGui::SliderFloat("g", &l->diffuse.g, 0, 1);
		ImGui::SliderFloat("b", &l->diffuse.b, 0, 1);
		ImGui::SliderFloat("a", &l->diffuse.a, 0, 1);

		ImGui::Text("specular");
		ImGui::SliderFloat("r", &l->specular.r, 0, 1);
		ImGui::SliderFloat("g", &l->specular.g, 0, 1);
		ImGui::SliderFloat("b", &l->specular.b, 0, 1);
		ImGui::SliderFloat("a", &l->specular.a, 0, 1);

	}



	LightTest* Clone() const {
		return new LightTest(*this);
	}
};