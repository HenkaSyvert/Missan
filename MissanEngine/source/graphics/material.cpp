#include "graphics/material.hpp"
#include "memory/database.hpp"

#include <stdio.h>
#include <iostream>

using namespace Missan;
using namespace ImGui;
using namespace std;

void Material::DisplayInInspector() {
	if (TreeNode("Material")) {
		ColorEdit4("ambient", (float*)&ambient);
		ColorEdit4("diffuse", (float*)&diffuse);
		ColorEdit4("specular", (float*)&specular);
		DragFloat("shininess", &shininess);
		//if (texture) texture->DisplayInInspector();
		if (BeginMenu("Shader")) {
			//if (MenuItem("Unlit")) shader = Shader::unlit;
			//if (MenuItem("Phong")) shader = Shader::diffuseSpecular;
			EndMenu();
		}
		TreePop();
	}
}

void Material::Load(const std::string& name) {

	IdType id = Object::GetUniqueId();
	Memory::Add<Material>(id);
	Material* m = Memory::Get<Material>(id);
	m->ambient = m->diffuse = m->specular = Color::white;
	m->shininess = 1;
	m->id = id;	//TODO: make id assignment part of ECS, this is stupid
	m->name = name; //TODO: assigning name per class is also stupid. 

	FILE* f = NULL;
	fopen_s(&f, name.c_str(), "r");
	if (f) fscanf_s(f, "%f %f %f %f %f %f %f %f %f %f",
		&m->ambient.r, &m->ambient.g, &m->ambient.b,
		&m->diffuse.r, &m->diffuse.g, &m->diffuse.b,
		&m->specular.r, &m->specular.g, &m->specular.b,
		&m->shininess);
	else {
		cout << "material.load: failed to open file\n";
	}

}