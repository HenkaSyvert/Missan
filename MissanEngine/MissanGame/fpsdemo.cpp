#include "missan.hpp"

using namespace Missan;

#define MAP_WIDTH 4
#define MAP_HEIGHT 4

glm::vec3 map[MAP_WIDTH * MAP_HEIGHT];

void GenerateRandomWorld() {
	int maxHeight = 2;
	int minHeight = -2;

	for (auto& cell : map) {
		cell.x = minHeight + rand() % (maxHeight - minHeight);
	}
}


void MakeRoom(GameObject& wall, GameObject& floor) {

}


void GenerateWorld() {

	GameObject wall;
	auto* rend = wall.AddComponent<Renderer>();
	rend->mesh_ptr = Resources::GetMesh("unitPlane");
	rend->texture_ptr = Resources::GetTexture("brickwall.png");
	Resources::GetTexture("stone2.png");
	Resources::GetTexture("stone3.jpg");
}


int main() {

	Engine::Initialize();

	GenerateWorld();

	Engine::Run();
	Engine::Terminate();

	return 0;
}