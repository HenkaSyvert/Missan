#include "graphics/material.hpp"


using namespace Missan;
using namespace ImGui;
using namespace std;

void Material::DisplayInInspector() {
	Text("material");
	ColorEdit4("ambient", (float*)&ambient);
	ColorEdit4("diffuse", (float*)&diffuse);
	ColorEdit4("specular", (float*)&specular);
	DragFloat("shininess", &shininess);
	if (texture) texture->DisplayInInspector();
	if (BeginMenu("Shader")) {
		if (MenuItem("Unlit")) shader = Shader::unlit;
		if (MenuItem("Phong")) shader = Shader::diffuseSpecular;
		EndMenu();
	}
}