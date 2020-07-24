#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "window.hpp"
#include "camera.hpp"
#include "components/transform.hpp"
#include "gameobject.hpp"

namespace missan {

	enum MENU_STATE { CAMERA, GAME_OBJECT };

	class GUI {

	private:
		Window* window_ptr;
		Camera* camera_ptr;
		
		GameObject* selectedGO;

		MENU_STATE menuState;
		void CameraMenu();
		void GameObjectMenu();

	public:
		GUI(Window& window, Camera& camera);
		void Run();
		void Exit();
		
		void SetSelectedGO(GameObject& go);


	};

}
