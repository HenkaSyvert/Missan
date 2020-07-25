#include "engine.hpp"

#include "window.hpp"
#include "input.hpp"
#include "time.hpp"
#include "resources.hpp"
#include "gui.hpp"
#include "gameobject.hpp"
#include "graphics.hpp"

#include <vector>
#include <iostream>

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

bool dummyFirstRun = true;	// temporary
// startFunc
void Engine::Run() {
	Time::Update();


	// PHYSICS



	// INPUT
	Input::Update();



	// GAME LOGIC
	std::vector<GameObject*>& gos = activeScene_ptr->gameObjects;

	// temporary, this is horribly inefficient
	if (dummyFirstRun) {
		for (auto* g : gos)
			for (auto* c : g->GetComponents())
				c->Start();
		dummyFirstRun = false;
	}
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->Update();
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->LateUpdate();



	// RENDERING
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->OnRender();



	// GUI
	GUI::Begin();
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->OnGUI();
	GUI::End();

}

void Engine::Terminate() {

	GUI::Terminate();
	Resources::Terminate();

}



void Engine::SetActiveScene(Scene& scene) {

	activeScene_ptr = &scene;

}

