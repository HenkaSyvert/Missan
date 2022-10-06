#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "internal.hpp"
#include "ecs/gameobject.hpp"
#include "input.hpp"
#include "graphics/window.hpp"
#include "physics/physics.hpp"


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
	
	while (!glfwWindowShouldClose(window)) {
		TimeUpdate();
		PhysicsUpdate();
		InputUpdate();
		
		for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
			PackedAssociativeArray* componentArray = Component::GetArrayById(componentTypeId);
			for (size_t index = 0; index < componentArray->count; index++) {
				((Component*)componentArray->GetByIndex(index))->Update();
			}
		}

		for (size_t componentTypeId = 0; componentTypeId < Component::numberOfTypes; componentTypeId++) {
			PackedAssociativeArray* componentArray = Component::GetArrayById(componentTypeId);
			for (size_t index = 0; index < componentArray->count; index++) {
				((Component*)componentArray->GetByIndex(index))->LateUpdate();
			}
		}
		
		GraphicsUpdate();		
		GuiUpdate();
		
		for (size_t gameObjectId : GameObject::gameObjectsToDestroy) {
			GameObject::DestroyImmediate(gameObjectId);
		}
		
		glfwSwapBuffers(window);
	}	

	GuiTerminate();
	glfwTerminate();

}

