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

	Scene* activeScene_ptr = nullptr;

	std::vector<GameObject*> gameObjectsToBeInstantiated;
	std::vector<GameObject*> gameObjectsToBeDestroyed;

}

// PUBLIC
void Engine::Initialize() {
	Window::Initialize(960, 720, "Missan 3D");
	Input::Initialize();
	Resources::Initialize();
	Graphics::Initialize();
	GUI::Initialize();

	activeScene_ptr = new Scene;
	
}

void Engine::Run() {
	Time::Update();
	// STARTUP
	std::vector<GameObject*>& gos = activeScene_ptr->gameObjects;
	
	for (auto* g : gameObjectsToBeInstantiated) {
		gos.push_back(g);
	}
	gameObjectsToBeInstantiated.clear();

	for (auto* g : gos)
		for (auto* c : g->components)
			c->Start();

	

	// MAIN LOOP
	while (!glfwWindowShouldClose(Window::GetHandle())) {
		Time::Update();


		// PHYSICS
		Physics::Update();



		// INPUT
		Input::Update();


		// GAME LOGIC	
		for (auto* g : gos)
			for (auto* c : g->components)
				c->Update();
		for (auto* g : gos)
			for (auto* c : g->components)
				c->LateUpdate();


		// RENDERING
		Graphics::Prepare();
		for (auto* g : gos) 
			for (auto* c : g->components)
				c->OnRender();
		


		// GUI
		GUI::Begin();
		for (auto* g : gos)
			for (auto* c : g->components)
				c->OnGUI();
		GUI::End();



		// Instantiations
		for (auto* g : gameObjectsToBeInstantiated) {
			gos.push_back(g);
			for (auto* c : g->components)
				c->Start();
		}
		gameObjectsToBeInstantiated.clear();



		// Destructions
		for (auto* g : gameObjectsToBeDestroyed) {
			bool found = false;
			
			for (Component* c : g->components)
				c->OnDestroy();

			for (int i = 0; !found && i < gos.size(); i++) {
				if (g == gos[i]) {
					gos.erase(gos.begin() + i);
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



Scene* Engine::GetActiveScene() {
	return activeScene_ptr;
}

void Engine::SetActiveScene(Scene& scene) {

	activeScene_ptr = &scene;

}

GameObject* Engine::Instantiate(GameObject& original) {
	gameObjectsToBeInstantiated.push_back(new GameObject(original));
	return gameObjectsToBeInstantiated.back();
}

void Engine::Destroy(GameObject* gameObject) {
	gameObjectsToBeDestroyed.push_back(gameObject);
}
