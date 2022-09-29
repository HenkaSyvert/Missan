#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace ImGui;

class Inspector : public Component {

public:

	GameObject* selected;


	void InspectTransform(Transform* t) {

		Text("Transform");
		DragFloat3("position", (float*)&t->position);
		DragFloat3("rotation", (float*)&t->rotation);
		DragFloat3("scale", (float*)&t->scale);

	}

	void GizmoLocalVectors(Transform* t) {



	}

	void OnClick() {



	}

	void OnGui() {

		

	}

};
