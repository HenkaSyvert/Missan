#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace std;
using namespace ImGui;

class Inspector : public Component {

public:

	int selectedGo = 0;

	vector<GameObject*> gos;

	void InspectGameObject(GameObject* g) {
		if (!g) return;
		Text(g->name.c_str());
		if (Button("select next Game Object")) SelectNextGameObject();

	}


	void SelectNextGameObject() {
		selectedGo++;
		if (selectedGo == gos.size())
			selectedGo = 0;
	}

	void Start() {
		gos = EcsGetGameObjects();


	}

	void OnGui() {

		GameObject* g = gos[selectedGo];
		InspectGameObject(g);
		
		for (auto& c : g->components) c->DisplayInInspector();
		

	}

	void Update() {

		if (Input::GetKeyDown(Keycode::Escape)) Engine::Quit();

	}

	Inspector* Clone() const {
		return new Inspector(*this);
	}

};
