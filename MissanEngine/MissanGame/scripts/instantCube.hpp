#pragma once

#include "missan.hpp"

using namespace Missan;

class InstantCube : public Component {

public:

	GameObject* prefab;
	bool allow = true;
	float coolDown = 0.5f;
	double timeStamp;

	void Start() {
		prefab = new GameObject();
		prefab->AddComponent<Renderer>();
		prefab->GetComponent<Renderer>()->mesh_ptr = Resources::GetMesh("unitCube");
		prefab->GetComponent<Renderer>()->texture_ptr = Resources::GetTexture("cat.png");

	}

	void Update() {
		if (!allow) {
			if (Time::time - timeStamp > coolDown)
				allow = true;
		}
		else if (Input::IsKeyPressed(GLFW_KEY_I)) {
			Scene& scene = Engine::activeScene;
			GameObject* g = Engine::Instantiate(*prefab);
			*g->GetComponent<Transform>() = *GetGameObject().GetComponent<Transform>();
			timeStamp = Time::time;
			allow = false;
		}
	}

	InstantCube* Clone() const { return new InstantCube(*this); }   // necessary for deep-cloning

};