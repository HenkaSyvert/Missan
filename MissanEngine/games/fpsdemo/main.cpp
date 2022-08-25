/*
 * This example shows how to make a simple game using the Missan API. 
 * The scripts demonstrate how to write custom components with user-defined behaviour, 
 * by overriding event-functions, and communicating between various components, 
 * and using functions and variables from missan API. 
 * 
 * The code contained in the "games" folder is separate from the engine code. 
 * This code represents the "user defined" code which merely uses the missan API to build a game. 
 *
 * Missan Engine does not have a graphical editor for piecing together games (though one might be
 * added in the future). In the meantime, games are assembled in code. The code in "main.cpp" is
 * analogous to the click-and-drag actions a user would do in a normal graphical UI in a game engine. 
 *
 *
 */


// include missan to gain access to the entire scripting API
#include "missan.hpp"

// these are our scripts
#include "scripts/fpscam.hpp"
#include "scripts/menu.hpp"
#include "scripts/weapon.hpp"
#include "scripts/movement.hpp"
#include "scripts/globals.hpp"
#include "scripts/destructible.hpp"

using namespace Missan;


//this function creates a small room with walls and floor. 
void MakeRoom() {

    // load the textures and meshes we'll need
    Texture* stone1 = Resources::GetTexture("stonefloor.png");
    Texture* stone2 = Resources::GetTexture("stone2.png");
    Texture* stone3 = Resources::GetTexture("stone3.jpg");
    Texture* bricks = Resources::GetTexture("brickwall.png");
    Mesh* plane = Resources::GetMesh("unitPlane");


    // make floor prefab
    GameObject floor;
    floor.AddComponent<Transform>();
    Renderer* rend = floor.AddComponent<Renderer>();
    rend->mesh_ptr = plane;
    rend->texture_ptr = stone1;
    Transform* trans = floor.GetComponent<Transform>();
    trans->scale = { cellWidth, cellBreadth, 1};
    trans->rotationDeg = { 90, 0, 0 };
    

    // instantiate floor tiles
    for (int x = 0; x < mapWidth; x++) {
        for (int z = 0; z < mapBreadth; z++) {
            GameObject* go = GameObject::Instantiate(floor);
            go->GetComponent<Transform>()->position = { x * cellWidth, 0, z * cellBreadth };
        }
    }
    

    // make wall prefab
    GameObject wall;
    wall.AddComponent<Transform>();
    rend = wall.AddComponent<Renderer>();
    rend->mesh_ptr = plane;
    rend->texture_ptr = bricks;
    trans = wall.GetComponent<Transform>();
    trans->scale = { cellWidth, cellHeight, 1 };


    // instantiate and rotate walls
    for (int x = 0; x < mapWidth; x++) {
        GameObject* go = GameObject::Instantiate(wall);
        go->GetComponent<Transform>()->position = { x * cellWidth, cellHeight / 2, -cellBreadth / 2 };
        go = GameObject::Instantiate(wall);
        go->GetComponent<Transform>()->position = { x * cellWidth, cellHeight / 2, (mapBreadth - 0.5f ) * cellBreadth };
    }
    for (int z = 0; z < mapBreadth; z++) {
        GameObject* go = GameObject::Instantiate(wall);
        Transform* trans = go->GetComponent<Transform>();
        trans->position = { -cellWidth / 2, cellHeight / 2, z * cellBreadth };
        trans->rotationDeg.y = 90;
        go = GameObject::Instantiate(wall);
        trans = go->GetComponent<Transform>();
        trans->position = { (mapWidth - 0.5f) * cellWidth, cellHeight / 2, z * cellBreadth };
        trans->rotationDeg.y = 90;
    }

}

// this function creates a player prefab with components attached and instantiates it in the game world. 
void MakePlayer() {

    // make player prefab
    GameObject player;      // base game object upon which the components will attach. 

    // attach some built-in components
    player.AddComponent<Transform>();           // represents location, rotation, scale, in the game world. 
    player.AddComponent<Camera>();              // through which the game world will be projected unto the screen. 
    player.AddComponent<Collider>();            // for detecting collisions against other colliders. 
    player.AddComponent<RigidBody>();           // for being simulated by the physics engine.

    // attach some of our own scripts
    player.AddComponent<Menu>();                // for displaying some information in menu
    player.AddComponent<Movement>();            // script for first person movement
    player.AddComponent<FPSCamera>();           // simple script for usual first person shooter camera
    player.AddComponent<Weapon>();              // for shooting small projectiles


    // give the player a thin collider to avoid collision with projectiles
    player.GetComponent<Collider>()->boundingBox.size = { 0.1,1,0.1 }; 

    // set the startin position
    //player.GetComponent<Transform>()->position.y = 100;

    GameObject* go = GameObject::Instantiate(player);       // creates a copy of the prefab and loads it into the game world. 
    Graphics::SetCamera(*go->GetComponent<Camera>());   
    
}

// this functions creates some rotating cubes which can be destroyed by the player. 
void PlaceDestructibles() {

    // make prefab of destructible cube
    GameObject cube;
    cube.AddComponent<Transform>();
    auto* rend = cube.AddComponent<Renderer>();
    rend->mesh_ptr = Resources::GetMesh("unitCube");
    rend->texture_ptr = Resources::GetTexture("missan_logo.png");
    cube.AddComponent<Collider>();
    cube.AddComponent<Destructible>();

    // instantiate some cubes
    for (int i = 0; i < 5; i++) {
        int x = rand() % mapWidth;
        int z = rand() % mapBreadth;
       
        GameObject* go = GameObject::Instantiate(cube);
        cube.GetComponent<Transform>()->position = { x * cellWidth, 1, z * cellBreadth };  
    }

}




// currently the game must provide its own main function, and must follow this structure
int main(int argc, char* argv[]){
    
    Engine::Initialize();       // allocates memory, registers callback functions etc...

    ///////////////////////////////////////////////////////////
    // Here is where you put your own code. Create a game world by adding game objects to a scene. 
    MakeRoom();
    MakePlayer();
    PlaceDestructibles();

    ///////////////////////////////////////////////////////////

    Engine::Run();          // start the game simulation
    Engine::Terminate();    // cleanup, free resources... 

    return 0;
}




