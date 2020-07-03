#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "window.h"
#include "camera.h"
#include "transform.h"

enum MENU_STATE {MAIN, CAMERA, WINDOW};

namespace missan {

	class GUI {

	private:
		Window* window_ptr;
		Camera* camera_ptr;

		MENU_STATE menuState = MAIN;
		void CameraMenu();


	public:
		GUI(Window& window, Camera& camera);
		void Run();
		void Exit();




	};

}
