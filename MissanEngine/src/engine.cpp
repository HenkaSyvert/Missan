#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "internal.hpp"
#include "ecs.hpp"
#include "input.hpp"
#include "window.hpp"
#include "physics.hpp"


using namespace Missan;
using namespace std;
using namespace glm;


static float _time = 0.0f;
static float _deltaTime = 0.0f;
const float& Time::time = _time;
const float& Time::deltaTime = _deltaTime;
	
static void TimeUpdate() {
	float timeStamp = (float)glfwGetTime();
	_deltaTime = timeStamp - _time;
	_time = timeStamp;
}

static GLFWwindow* window = nullptr;

void Engine::Initialize() {
	window = WindowInitialize();
	InputInitialize(window);
	GraphicsInitialize();
	GuiInitialize(window);
}

void Engine::Quit() {

	glfwSetWindowShouldClose(window, GLFW_TRUE);

}

void Engine::Run() {
	TimeUpdate();
	GameObjectDoInstantiations();
	
	while (!glfwWindowShouldClose(window)) {
		TimeUpdate();
		PhysicsUpdate();
		InputUpdate();
		for(auto* g : GameObject::instances) g->Update();
		for(auto* g : GameObject::instances) g->LateUpdate();
		GraphicsUpdate();		
		GuiUpdate();
		GameObjectDoInstantiations();
		GameObjectDoDestructions();
		glfwSwapBuffers(window);
	}	

	GuiTerminate();
	glfwTerminate();

}

