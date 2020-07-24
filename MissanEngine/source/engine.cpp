#include "engine.hpp"

#include "window.hpp"
#include "input.hpp"
#include "resources.hpp"
#include "gui.hpp"

using namespace missan;

namespace {



}

// PUBLIC
void Engine::Initialize() {

	Window::Initialize(960, 720, "Missan 3D");
	Input::Initialize();
	Resources::Initialize();
	GUI::Initialize();

}

bool Engine::Run() {


	return true;
}

void Engine::Terminate() {



}
