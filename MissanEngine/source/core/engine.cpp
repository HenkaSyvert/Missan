#include "core/engine.hpp"

#include "missanpch.hpp"
#include "core/window.hpp"
#include "core/input.hpp"
#include "core/time.hpp"
#include "core/resources.hpp"
#include "core/gui.hpp"
#include "gameobject.hpp"
#include "graphics/graphics.hpp"


using namespace missan;

namespace {

	Scene* activeScene_ptr = nullptr;

}

// PUBLIC
void Engine::Initialize() {
	Window::Initialize(960, 720, "Missan 3D");
	Input::Initialize();
	Resources::Initialize();
	Graphics::Initialize();
	GUI::Initialize();
	
}

void Engine::Run() {
	// TODO: proper Entity-Component system. current method is very memory-access inefficient

	// STARTUP
	std::vector<GameObject*>& gos = activeScene_ptr->gameObjects;
	for (auto* g : gos)
		for (auto* c : g->components)
			c->Start();

	// MAIN LOOP
	while (!glfwWindowShouldClose(Window::GetHandle())) {
		Time::Update();
			
		
		// PHYSICS
		for (auto* g : gos)
			for (auto* c : g->components)
				c->OnPhysicsUpdate();

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


		glfwSwapBuffers(Window::GetHandle());
	}	
}

void Engine::Terminate() {
	GUI::Terminate();
	Resources::Terminate();
	glfwTerminate();

}



void Engine::SetActiveScene(Scene& scene) {

	activeScene_ptr = &scene;

}

