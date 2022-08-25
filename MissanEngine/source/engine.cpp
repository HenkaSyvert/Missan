#include "engine.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "internal.hpp"
#include "gameobject.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "time.hpp"
#include "window.hpp"
#include "graphics.hpp"
#include "physics.hpp"

#include <vector>

using namespace Missan;
using namespace std;
using namespace glm;

static vector<GameObject*> gameObjectsToBeInstantiated;
static vector<GameObject*> gameObjectsToBeDestroyed;
static vector<GameObject*> gameObjects;

static float _time = 0.0f;
static float _deltaTime = 0.0f;
const float& Time::time = _time;
const float& Time::deltaTime = _deltaTime;
	
static void update_time() {
	float timeStamp = (float)glfwGetTime();
	_deltaTime = timeStamp - _time;
	_time = timeStamp;
}

static GLFWwindow* window = nullptr;

void Engine::Initialize() {
	window = WindowInitialize();
	InputInitialize(window);
	ResourcesInitialize();
	GraphicsInitialize();
	GuiInitialize(window);

}

void Engine::Run() {
	update_time();
	
	for (auto* g : gameObjectsToBeInstantiated) {
		gameObjects.push_back(g);
	}
	gameObjectsToBeInstantiated.clear();

	for (auto* g : gameObjects) for (auto* c : g->components) c->Start();

	
	while (!glfwWindowShouldClose(window)) {
		update_time();

		PhysicsUpdate(gameObjects);

		InputUpdate();


		for (auto* g : gameObjects) for (auto* c : g->components) c->Update();
		for (auto* g : gameObjects) for (auto* c : g->components) c->LateUpdate();

		GraphicsUpdate(gameObjects);
		
		GuiUpdate(gameObjects);

		for (auto* g : gameObjectsToBeInstantiated) {
			gameObjects.push_back(g);
			for (auto* c : g->components)
				c->Start();
		}
		gameObjectsToBeInstantiated.clear();



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

		
		glfwSwapBuffers(window);
	}	
}

void Engine::Terminate() {
	GuiTerminate();
	ResourcesTerminate();
	glfwTerminate();

}

GameObject* Engine::Instantiate(GameObject& original) {
	gameObjectsToBeInstantiated.push_back(new GameObject(original));
	return gameObjectsToBeInstantiated.back();
}

void Engine::Destroy(GameObject* gameObject) {
	gameObjectsToBeDestroyed.push_back(gameObject);
}
