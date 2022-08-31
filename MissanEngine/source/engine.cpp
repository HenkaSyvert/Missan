#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "internal.hpp"
#include "gameobject.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "window.hpp"
#include "graphics.hpp"
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

void Engine::Run() {
	TimeUpdate();
	EcsComponentsStart();
	EcsGameObjectInstantiate();
	
	while (!glfwWindowShouldClose(window)) {
		TimeUpdate();
		PhysicsUpdate();
		InputUpdate();
		EcsComponentsUpdate();
		EcsComponentsLateUpdate();
		GraphicsUpdate();		
		GuiUpdate();
		EcsGameObjectInstantiate();
		EcsGameObjectDestroy();
		glfwSwapBuffers(window);
	}	

	GuiTerminate();
	glfwTerminate();

}

