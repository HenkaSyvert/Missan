#include "core/engine.hpp"

#include "missanpch.hpp"
#include "core/window.hpp"
#include "core/input.hpp"
#include "core/time.hpp"
#include "core/resources.hpp"
#include "core/gui.hpp"
#include "gameobject.hpp"
#include "graphics/graphics.hpp"
#include "components/collider.hpp"
#include "components/transform.hpp"

using namespace missan;

namespace {

	Scene* activeScene_ptr = nullptr;

	void CheckCollisions(std::vector<GameObject*>& gameObjects) {
		for (auto* a : gameObjects) {
			Collider* ca = a->GetComponent<Collider>();
			if (ca == nullptr) continue;

			for (auto* b : gameObjects) {
				if (a == b) continue;
				Collider* cb = b->GetComponent<Collider>();
				if (cb == nullptr) continue;

				float overlap = ca->OverlapsWith(cb);
				if (overlap != 0) {
					// collision happened, do something
					std::cout << "collision detected\n";
					glm::vec3 aCenter = a->GetComponent<Transform>()->position;
					glm::vec3 bCenter = b->GetComponent<Transform>()->position;
					glm::vec3 displacementDirection(b - a);
					displacementDirection = glm::normalize(displacementDirection);
					a->GetComponent<Transform>()->position += displacementDirection * (overlap / 2);
					b->GetComponent<Transform>()->position -= displacementDirection * (overlap / 2);
				}

			}
		}
	}

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
		CheckCollisions(gos);



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



Scene* Engine::GetActiveScene() {
	return activeScene_ptr;
}

void Engine::SetActiveScene(Scene& scene) {

	activeScene_ptr = &scene;

}

GameObject* Engine::Instantiate(GameObject& original) {
	activeScene_ptr->gameObjects.push_back(new GameObject(original));
	return activeScene_ptr->gameObjects.back();
}

