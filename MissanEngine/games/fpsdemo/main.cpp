// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

// load some scripts for demonstration
#include "scripts/fpscam.hpp"
#include "scripts/menu.hpp"
#include "scripts/weapon.hpp"
#include "scripts/movement.hpp"

using namespace Missan;


// some data for generating a simple map
constexpr int mapWidth   = 1;
constexpr int mapBreadth = 2;

constexpr float cellWidth   = 5.0f;
constexpr float cellHeight  = 2.0f;
constexpr float cellBreadth = 5.0f;



void MakeMap() {

    Texture* stone1 = Resources::GetTexture("stonefloor.png");
    Texture* stone2 = Resources::GetTexture("stone2.png");
    Texture* stone3 = Resources::GetTexture("stone3.jpg");
    Texture* bricks = Resources::GetTexture("brickwall.png");

    Mesh* plane = Resources::GetMesh("unitPlane");


    // make floor
    GameObject floor;
    Renderer* rend = floor.AddComponent<Renderer>();
    rend->mesh_ptr = plane;
    rend->texture_ptr = stone1;
    Transform* trans = floor.GetComponent<Transform>();
    trans->scale = { cellWidth, cellBreadth, 1};
    trans->rotationDeg = { 90, 0, 0 };
   
    for (int x = 0; x < mapWidth; x++) {
        for (int z = 0; z < mapBreadth; z++) {

            GameObject* go = Engine::Instantiate(floor);
            go->GetComponent<Transform>()->position = { x * cellWidth, 0, z * cellBreadth };

        }
    }
    

    // make walls along the edges of map
    GameObject wall;
    rend = wall.AddComponent<Renderer>();
    rend->mesh_ptr = plane;
    rend->texture_ptr = bricks;
    trans = wall.GetComponent<Transform>();
    trans->scale = { cellWidth, cellHeight, 1 };

    for (int x = 0; x < mapWidth; x++) {
        GameObject* go = Engine::Instantiate(wall);
        go->GetComponent<Transform>()->position = { x * cellWidth, cellHeight / 2, -cellBreadth / 2 };
        go = Engine::Instantiate(wall);
        go->GetComponent<Transform>()->position = { x * cellWidth, cellHeight / 2, (mapBreadth - 0.5f ) * cellBreadth };
    }

    for (int z = 0; z < mapBreadth; z++) {
        GameObject* go = Engine::Instantiate(wall);
        Transform* trans = go->GetComponent<Transform>();
        trans->position = { -cellWidth / 2, cellHeight / 2, z * cellBreadth };
        trans->rotationDeg.y = 90;
        go = Engine::Instantiate(wall);
        trans = go->GetComponent<Transform>();
        trans->position = { (mapWidth - 0.5f) * cellWidth, cellHeight / 2, z * cellBreadth };
        trans->rotationDeg.y = 90;
    }


}

void MakePlayer() {

    GameObject player;
    player.AddComponent<Camera>();
    player.AddComponent<Menu>();
    player.AddComponent<FPSCamera>();
    player.AddComponent<Movement>();   
    player.AddComponent<Weapon>();
    player.GetComponent<Transform>()->position.y = 1.2f;

    GameObject* go = Engine::Instantiate(player);
    Graphics::SetCamera(*go->GetComponent<Camera>());
    
}





// the game must provide its own main, and must follow this structure
int main(int argc, char* argv[]){
    
    Engine::Initialize();

    ///////////////////////////////////////////////////////////
    // Here is where you put your own code to add GameObjects to Scene
    MakeMap();
    MakePlayer();


    ///////////////////////////////////////////////////////////

    Engine::Run();

    Engine::Terminate();

    return 0;
}




