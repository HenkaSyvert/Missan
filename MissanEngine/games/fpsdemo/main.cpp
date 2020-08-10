#include "missan.hpp"

#include "scripts/fpscam.hpp"
#include "scripts/weapon.hpp"

using namespace Missan;

void FpsDemo() {

	GameObject camera;
	camera.AddComponent<Camera>();
	camera.AddComponent<FPSCamera>();




}

int main() {

	Engine::Initialize();
	FpsDemo();
	Engine::Run();
	Engine::Terminate();
	return 0;
}