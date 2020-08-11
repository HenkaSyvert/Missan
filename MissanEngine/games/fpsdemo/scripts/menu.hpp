#pragma once

#include "missan.hpp"
#include "weapon.hpp"


using namespace Missan;

class Menu : public Component {

public:

	// for fpscam script
	bool canMoveCam = true;
	bool isPaused = false;


	// key to pause game, specifically fpscam script
	int pauseKey = GLFW_KEY_ESCAPE;

	// to avoid multiple keypresses
	float delay = 0.4f;

	// timer for key press
	float timeStamp;

	bool canPressKey = true;


	// for dispaying info about weapon
	Weapon* weapon;



	void Start() {
		timeStamp = Time::unscaledTime;
	}

	void Update() {

		if (!canPressKey) {
			if (Time::unscaledTime - timeStamp > delay) {
				canPressKey = true;
				timeStamp = Time::unscaledTime;
			}
		}
		else if (Input::IsKeyPressed(pauseKey)) {
			isPaused = !isPaused;
			canMoveCam = !isPaused;
		}

	}

	void OnGUI() {
		ImGui::Text("press ESCAPE to pause game");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}



	Menu* Clone() const { return new Menu(*this); }


};

