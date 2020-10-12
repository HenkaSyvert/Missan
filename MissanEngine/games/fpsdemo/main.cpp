// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

// load some scripts for demonstration
#include "scripts/fpscam.hpp"
#include "scripts/menu.hpp"
#include "scripts/weapon.hpp"
#include "scripts/movement.hpp"
#include "scripts/globals.hpp"
#include "scripts/destructible.hpp"

using namespace Missan;



void MakeRoom() {

    Texture* stone1 = Resources::GetTexture("stonefloor.png");
    Texture* stone2 = Resources::GetTexture("stone2.png");
    Texture* stone3 = Resources::GetTexture("stone3.jpg");
    Texture* bricks = Resources::GetTexture("brickwall.png");

    Mesh* plane = Resources::GetMesh("unitPlane");


    // make floor
    GameObject floor;
    floor.AddComponent<Transform>();
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
    wall.AddComponent<Transform>();
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

// makes a single graphical column at xz
void MakeColumn(int x, int z) {

    GameObject wall;
    wall.AddComponent<Transform>();
    Renderer* rend = wall.AddComponent<Renderer>();
    rend->mesh_ptr = Resources::GetMesh("unitPlane");
    rend->texture_ptr = Resources::GetTexture("stone3.jpg");
    Transform* trans = wall.GetComponent<Transform>();
    trans->scale = { cellWidth, cellHeight, 1 };

    for (int i = 0; i < 4; i++) {
        GameObject* go = Engine::Instantiate(wall);
        trans = go->GetComponent<Transform>();
        glm::vec2 pos = { x * cellWidth, z * cellBreadth };
        trans->position = { pos.x + cellWidth/2* cosf(3.1415 / 2 * i), cellHeight / 2, pos.y + cellBreadth/2* sinf(3.1415 / 2 * i) };
        trans->rotationDeg.y = 90 * (i+1);
    }


}

// add some "columns" to make the room interesting
std::vector<glm::ivec2> MakeColumns() {

    // how many % of room we want to be columns
    float percentage = 0.1f;

    int count = mapWidth* mapBreadth* percentage;
    std::vector<glm::ivec2> coords;


    for (int i = 0; i < count; ) {
        glm::ivec2 xz = { rand() % mapWidth, rand() % mapBreadth };
        bool found = false;
        for (auto& v : coords) {
            // player always starts at (0,0)
            if (xz == v || xz == glm::ivec2(0,0)) {
                found = true;
                break;
            }
        }
        if (!found) {
            coords.push_back(xz);
            i++;
        }
    }

    for (auto& v : coords)
        MakeColumn(v.x, v.y);


    return coords;

}



void MakePlayer(std::vector<glm::ivec2>& columns) {

    GameObject player;
    player.AddComponent<Transform>();
    player.AddComponent<Camera>();
    player.AddComponent<Menu>();
    player.AddComponent<FPSCamera>();
    Movement* movement = player.AddComponent<Movement>();   
    movement->columns = columns;
    player.AddComponent<Weapon>();
    
    player.AddComponent<Collider>();
    player.AddComponent<RigidBody>();
    player.GetComponent<Collider>()->boundingBox.size = { 0.1,1,0.1 };  // to avoid collision with projectile

    GameObject* go = Engine::Instantiate(player);
    Graphics::SetCamera(*go->GetComponent<Camera>());
    go->GetComponent<Weapon>()->isPaused = &go->GetComponent<Menu>()->isPaused;

    
}

void PlaceDestructibles(std::vector<glm::ivec2>& cols) {

    GameObject g;
    g.AddComponent<Transform>();
    auto* rend = g.AddComponent<Renderer>();
    rend->mesh_ptr = Resources::GetMesh("unitCube");
    rend->texture_ptr = Resources::GetTexture("missan_logo.png");
    g.AddComponent<Collider>();
    g.AddComponent<Destructible>();

    float percentage = 0.3f;
    int count = 3;// mapWidth* mapBreadth* percentage;

    for (int i = 0; i < count; ) {
        int x = rand() % mapWidth;
        int z = rand() % mapBreadth;


        bool insideCol = false;
        // we don't want to place destructible inside a column
        for (auto& c : cols) {
            if (c.x == x && c.y == z) {
                insideCol = true;
                break;
            }
        }

        if (!insideCol) {
            GameObject* go = Engine::Instantiate(g);
            g.GetComponent<Transform>()->position = { x * cellWidth, 1, z * cellBreadth };
            i++;
        }

    }

}





// the game must provide its own main, and must follow this structure
int main(int argc, char* argv[]){
    
    Engine::Initialize();

    ///////////////////////////////////////////////////////////
    // Here is where you put your own code to add GameObjects to Scene
    MakeRoom();
    auto columns = MakeColumns();
    MakePlayer(columns);
    PlaceDestructibles(columns);

    ///////////////////////////////////////////////////////////

    Engine::Run();

    Engine::Terminate();

    return 0;
}




