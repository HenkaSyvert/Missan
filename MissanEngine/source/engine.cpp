#include "engine.hpp"

#include "window.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "gui.hpp"
#include "gameobject.hpp"

#include <vector>

using namespace missan;

namespace {

	Scene* activeScene_ptr = nullptr;


}

// PUBLIC
void Engine::Initialize() {

	Window::Initialize(960, 720, "Missan 3D");
	Input::Initialize();
	Resources::Initialize();
	GUI::Initialize();

}

void Engine::Run() {
	std::vector<GameObject*>& gos = activeScene_ptr->gameObjects;
	
	// temporary, this is horribly inefficient
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->Update();
	for (auto* g : gos)
		for (auto* c : g->GetComponents())
			c->LateUpdate();

	// OnGUI()
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

