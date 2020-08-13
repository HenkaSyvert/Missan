#pragma once

#include "missan.hpp"
#include "weapon.hpp"


using namespace Missan;

class Menu : public Component {

public:

	bool isPaused = false;

	// key to pause game, specifically fpscam script
	int pauseKey = GLFW_KEY_E;

	// to avoid multiple keypresses
	float delay = 0.5f;

	// timer for key press
	float timeStamp;

	bool canPressKey = true;


	// for dispaying info about weapon
	Weapon* weapon;



	void Start() {
		timeStamp = Time::unscaledTime;
		Window::SetIsCursorVisible(false);
	}

	void Update() {

		if (!canPressKey) {
			if (Time::unscaledTime - timeStamp > delay) {
				canPressKey = true;			
			}
		}
		
		if (canPressKey && Input::IsKeyPressed(pauseKey)) {
			isPaused = !isPaused;
			Window::SetIsCursorVisible(isPaused);
			canPressKey = false;
			timeStamp = Time::unscaledTime;
		}

	}

	void OnGUI() {
		ImGui::Text("press E to pause game");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}



	Menu* Clone() const { return new Menu(*this); }


};

