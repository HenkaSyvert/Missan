#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace std;
using namespace ImGui;

class Inspector : public Component {

public:
	GameObject* selected = nullptr;
	vector<GameObject*> gos;

	void Start() {
		gos = EcsGetGameObjects();
		selected = gos[0];
	}

	void OnGui() {
		gos = EcsGetGameObjects();
		if (BeginMenu("Game Objects")) {
			for (auto& g : gos) {
				if (MenuItem(g->name.c_str())) selected = g;
			}
			EndMenu();
		}
		
		
		for (auto& c : selected->components) c->DisplayInInspector();
		

	}

	void Update() {

		if (Input::GetKeyDown(Keycode::Escape)) Engine::Quit();

	}

};
