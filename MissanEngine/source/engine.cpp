#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "internal.hpp"
#include "ecs/gameobject.hpp"
#include "input.hpp"
#include "graphics/window.hpp"
#include "physics/physics.hpp"

#include <iostream>
#include <stdio.h>

#define MISSAN_DEBUG_ENGINE 0
static bool isDebugStepping = false;

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
	MemoryInitialize();
	ResourcesInitialize();
	if (MISSAN_DEBUG_ENGINE)std::cout << "Engine::Initialize() done\n\n";
}

void Engine::Quit() {

	glfwSetWindowShouldClose(window, GLFW_TRUE);

}

void Engine::Run() {
	if (MISSAN_DEBUG_ENGINE)cout << "\nEngine::Run():\n";
	TimeUpdate();
	
	while (!glfwWindowShouldClose(window)) {


		if (MISSAN_DEBUG_ENGINE)cout << "TimeUpdate():\n";
		TimeUpdate();

		if (MISSAN_DEBUG_ENGINE)cout << "PhysicsUpdate():\n";
		PhysicsUpdate();

		if (MISSAN_DEBUG_ENGINE)cout << "InputUpdate():\n";
		InputUpdate();
		
		if (MISSAN_DEBUG_ENGINE)cout << "Component::UpdateAll():\n";
		Component::UpdateAll();

		if (MISSAN_DEBUG_ENGINE)cout << "Component::LateUpdateAll():\n";
		Component::LateUpdateAll();
			
		if (MISSAN_DEBUG_ENGINE)cout << "GraphicsUpdate():\n";
		GraphicsUpdate();		

		if (MISSAN_DEBUG_ENGINE)cout << "GuiUpdate():\n";
		GuiUpdate();
		
		if (MISSAN_DEBUG_ENGINE)cout << "GameObject::Destroy():\n";
		for (size_t gameObjectId : GameObject::gameObjectsToDestroy) {
			GameObject::DestroyImmediate(gameObjectId);
		}
		
		glfwSwapBuffers(window);
		if (isDebugStepping) {
			if (MISSAN_DEBUG_ENGINE)cout << "\npress Enter to continue...\n";
			getchar();
		}
	}	

	GuiTerminate();
	glfwTerminate();

}

