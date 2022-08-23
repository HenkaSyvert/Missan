#include "core/engine.hpp"

#include "missanpch.hpp"
#include "core/gameobject.hpp"
#include "core/gui.hpp"
#include "core/input.hpp"
#include "core/resources.hpp"
#include "core/time.hpp"
#include "core/window.hpp"
#include "graphics/graphics.hpp"
#include "physics/physics.hpp"

using namespace Missan;

namespace {


	std::vector<GameObject*> gameObjectsToBeInstantiated;
	std::vector<GameObject*> gameObjectsToBeDestroyed;
	std::vector<GameObject*> gameObjects;

	float _time = 0.0f;
	float _deltaTime = 0.0f;
	
	void update_time() {
		double timeStamp = glfwGetTime();
		_deltaTime = (float)timeStamp - _time;
		_time = (float)timeStamp;

	}



	glm::vec3 mousePosition_;
	glm::vec3 mouseDelta_;
	const Keycode keycodes[] = {
		Keycode::Space		  ,
		Keycode::Apostrophe     ,
		Keycode::Comma          ,
		Keycode::Minus          ,
		Keycode::Period         ,
		Keycode::Slash          ,
		Keycode::Alpha0         ,
		Keycode::Alpha1         ,
		Keycode::Alpha2         ,
		Keycode::Alpha3         ,
		Keycode::Alpha4         ,
		Keycode::Alpha5         ,
		Keycode::Alpha6         ,
		Keycode::Alpha7         ,
		Keycode::Alpha8         ,
		Keycode::Alpha9         ,
		Keycode::Semicolon      ,
		Keycode::Equal          ,
		Keycode::A              ,
		Keycode::B              ,
		Keycode::C              ,
		Keycode::D              ,
		Keycode::E              ,
		Keycode::F              ,
		Keycode::G              ,
		Keycode::H              ,
		Keycode::I              ,
		Keycode::J              ,
		Keycode::K              ,
		Keycode::L              ,
		Keycode::M              ,
		Keycode::N              ,
		Keycode::O              ,
		Keycode::P              ,
		Keycode::Q              ,
		Keycode::R              ,
		Keycode::S              ,
		Keycode::T              ,
		Keycode::U              ,
		Keycode::V              ,
		Keycode::W              ,
		Keycode::X              ,
		Keycode::Y              ,
		Keycode::Z              ,
		Keycode::LeftBracket    ,
		Keycode::Backslash      ,
		Keycode::RightBracket   ,
		Keycode::GraveAccent    ,
		Keycode::Escape         ,
		Keycode::Enter          ,
		Keycode::Tab            ,
		Keycode::Backspace      ,
		Keycode::Insert         ,
		Keycode::Delete         ,
		Keycode::Right          ,
		Keycode::Left           ,
		Keycode::Down           ,
		Keycode::Up             ,
		Keycode::PageUp         ,
		Keycode::PageDown       ,
		Keycode::Home           ,
		Keycode::End            ,
		Keycode::CapsLock       ,
		Keycode::ScrollLock     ,
		Keycode::NumLock        ,
		Keycode::Pause          ,
		Keycode::F1             ,
		Keycode::F2             ,
		Keycode::F3             ,
		Keycode::F4             ,
		Keycode::F5             ,
		Keycode::F6             ,
		Keycode::F7             ,
		Keycode::F8             ,
		Keycode::F9             ,
		Keycode::F10            ,
		Keycode::F11            ,
		Keycode::Keypad0        ,
		Keycode::Keypad1        ,
		Keycode::Keypad2        ,
		Keycode::Keypad3        ,
		Keycode::Keypad4        ,
		Keycode::Keypad5        ,
		Keycode::Keypad6        ,
		Keycode::Keypad7        ,
		Keycode::Keypad8        ,
		Keycode::Keypad9        ,
		Keycode::KeypadDecimal  ,
		Keycode::KeypadDivide   ,
		Keycode::KeypadMultiply ,
		Keycode::KeypadSubtract ,
		Keycode::KeypadAdd      ,
		Keycode::KeypadEnter    ,
		Keycode::LeftShift      ,
		Keycode::LeftControl    ,
		Keycode::LeftAlt        ,
		Keycode::LeftSuper      ,
		Keycode::RightShift     ,
		Keycode::RightControl   ,
		Keycode::RightAlt       ,
		Keycode::RightSuper     ,
		Keycode::Menu
	};


	std::unordered_map<Keycode, bool> isKeyDown, isKeyUp;
	bool isButtonDown[] = { false }, isButtonUp[] = { false };
	void init_maps() {
		for (auto k : keycodes) {
			isKeyDown.emplace(k, false);
			isKeyUp.emplace(k, false);
		}
	}

	void glfw_keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Keycode k = Keycode(key);
		if (action == GLFW_PRESS) isKeyDown[k] = true;
		else if (action == GLFW_RELEASE) isKeyUp[k] = true;
	}

	void glfw_mousebutton_callback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) isButtonDown[button] = true;
		else if (action == GLFW_RELEASE) isButtonUp[button] = true;
	}

	void input_update() {
		glm::vec3 old = mousePosition_;
		double x, y;
		glfwGetCursorPos(Window::GetHandle(), &x, &y);
		mousePosition_.x = (float)x;
		mousePosition_.y = (float)y;
		mouseDelta_ = mousePosition_ - old;
		for (auto& k : isKeyDown) k.second = false;
		for (auto& k : isKeyUp)k.second = false;
		for (int b = 0; b < 5; b++) {
			isButtonDown[b] = false;
			isButtonUp[b] = false;
		}
		glfwPollEvents();
	}

	void input_init() {
		glfwSetKeyCallback(Window::GetHandle(), glfw_keyboard_callback);
		glfwSetMouseButtonCallback(Window::GetHandle(), glfw_mousebutton_callback);
		double x, y;
		glfwGetCursorPos(Window::GetHandle(), &x, &y);
		mousePosition_.x = (float)x;
		mousePosition_.y = (float)y;
		init_maps();
		input_update();
	}

	




}




const float& Time::time = _time;
const float& Time::deltaTime = _deltaTime;


const glm::vec3& Input::mousePosition = mousePosition_;
const glm::vec3& Input::mouseDelta = mouseDelta_;

bool Input::GetKeyDown(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes) if (Input::GetKeyDown(k)) return true;
		return false;
	}
	return isKeyDown[keycode];
}

bool Input::GetKeyUp(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes) if (Input::GetKeyUp(k)) return true;
		return false;
	}
	return isKeyUp[keycode];
}

bool Input::GetKey(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes) if (Input::GetKey(k)) return true;
		return false;
	}
	return glfwGetKey(Window::GetHandle(), (int)keycode) == GLFW_PRESS;
}

bool Input::GetMouseButton(MouseButton button) {
	return glfwGetMouseButton(Window::GetHandle(), (int)button) == GLFW_PRESS;
}

bool Input::GetMouseButtonDown(MouseButton button) {
	return isButtonDown[(int)button];
}

bool Input::GetMouseButtonUp(MouseButton button) {
	return isButtonUp[(int)button];
}





// PUBLIC
void Engine::Initialize() {
	Window::Initialize(960, 720, "Missan 3D");
	input_init();
	Resources::Initialize();
	Graphics::Initialize();
	GUI::Initialize();

	
}

void Engine::Run() {
	update_time();
	// STARTUP
	
	for (auto* g : gameObjectsToBeInstantiated) {
		gameObjects.push_back(g);
	}
	gameObjectsToBeInstantiated.clear();

	for (auto* g : gameObjects)
		for (auto* c : g->components)
			c->Start();

	

	// MAIN LOOP
	while (!glfwWindowShouldClose(Window::GetHandle())) {
		update_time();


		// PHYSICS
		Physics::Update(gameObjects);



		// INPUT
		input_update();


		// GAME LOGIC	
		for (auto* g : gameObjects)
			for (auto* c : g->components)
				c->Update();
		for (auto* g : gameObjects)
			for (auto* c : g->components)
				c->LateUpdate();


		// RENDERING
		Graphics::Prepare();
		for (auto* g : gameObjects)
			for (auto* c : g->components)
				c->OnRender();
		


		// GUI
		GUI::Begin();
		for (auto* g : gameObjects)
			for (auto* c : g->components)
				c->OnGUI();
		GUI::End();



		// Instantiations
		for (auto* g : gameObjectsToBeInstantiated) {
			gameObjects.push_back(g);
			for (auto* c : g->components)
				c->Start();
		}
		gameObjectsToBeInstantiated.clear();



		// Destructions
		for (auto* g : gameObjectsToBeDestroyed) {
			bool found = false;
			
			for (Component* c : g->components)
				c->OnDestroy();

			for (unsigned int i = 0; !found && i < gameObjects.size(); i++) {
				if (g == gameObjects[i]) {
					gameObjects.erase(gameObjects.begin() + i);
					delete g;
					found = true;
				}

			}
		}
		gameObjectsToBeDestroyed.clear();

		
		glfwSwapBuffers(Window::GetHandle());
	}	
}

void Engine::Terminate() {
	GUI::Terminate();
	Resources::Terminate();
	glfwTerminate();

}

GameObject* Engine::Instantiate(GameObject& original) {
	gameObjectsToBeInstantiated.push_back(new GameObject(original));
	return gameObjectsToBeInstantiated.back();
}

void Engine::Destroy(GameObject* gameObject) {
	gameObjectsToBeDestroyed.push_back(gameObject);
}
