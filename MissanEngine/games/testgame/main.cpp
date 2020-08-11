// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

// load some scripts for demonstration
#include "scripts/fpscam.hpp"
#include "scripts/FloatScript.hpp"
#include "scripts/menu.hpp"
#include "scripts/weapon.hpp"

using namespace Missan;

bool moveCam = true;

// script to make a simple scene
void StandardMap() {

    // lets create some prefabs, i.e. premade template gameobjects
    // which we can later instantiate copies of in the scene
    GameObject wallPrefab;                                          // GameObjects are created with a Transform Component already attached
    Renderer* renderer = wallPrefab.AddComponent<Renderer>();       // Renderers are what makes a GameObject visible         
    renderer->texture_ptr = Resources::GetTexture("brickwall.png"); // Assets can be accessed as such
    auto* unitPlane = Resources::GetMesh("unitPlane");              // or save a pointer like this if that's more convenient
    renderer->mesh_ptr = unitPlane;
    Transform* transform = wallPrefab.GetComponent<Transform>();    // We can get pointers to any attached Component this way
    transform->scale = { 10,2,1 };                                  // This will also apply to all copies we make
    wallPrefab.AddComponent<Collider>();                            // Allows us to detect collisions against this GameObject
    //wallPrefab.AddComponent<FloatScript>();                       // We can add our own custom-made scripts if we want. This one just makes it "float" 

    GameObject floorPrefab;
    renderer = floorPrefab.AddComponent<Renderer>();
    renderer->mesh_ptr = unitPlane;
    renderer->texture_ptr = Resources::GetTexture("stonefloor.png");
    transform = floorPrefab.GetComponent<Transform>();
    transform->scale = { 10,10,1 };
    transform->rotationDeg = { 90,0,0 };
    transform->position.y = -1; 
    floorPrefab.AddComponent<Collider>();

    GameObject camera;                              // The GameObject holding the camera
    camera.AddComponent<Camera>();                  // The actual Camera, through which we can view the world
    camera.AddComponent<FPSCamera>();               // our custom-made script to make it behave like a flying FPS style camera
    transform = camera.GetComponent<Transform>();
    transform->rotationDeg = { -15,180,0 };
    transform->position = { 0,2,-10 };
    camera.AddComponent<Collider>();                // so we know if we collide into things
    camera.AddComponent<Weapon>();

    //GameObject menuManager;                         // We need a GameObject in order for the menu to be active in the game
    //menuManager.AddComponent<Menu>();               // and this script does the menu

    

    // Now we instantiate the objects
    GameObject* floor = Engine::Instantiate(floorPrefab);      // Instantiations are made to the currently active Scene
    GameObject* go;
    for (int i = 0; i < 3; i++) {                           // We can make several copies of the same prefab
        go = Engine::Instantiate(wallPrefab);               // and keep make the changes to the copy instead of the original
        transform = go->GetComponent<Transform>();
        transform->position = { 5 * cos(i*3.1415 * 0.5),0,5 * sin(i*3.1415 * 0.5) };
        transform->rotationDeg = { 0,90 + 90 * i,0 };
    }


    // and this is somewhat messy, and will be simplified sometime in the future
    // but we need to fix some pointers so they point to the GameObjects in the scene
    // rather than to the uninstantiated prefab
    GameObject* cameraGo = Engine::Instantiate(camera);
    Graphics::SetCamera(*cameraGo->GetComponent<Camera>());     // This is temporary, should be global
    //go = Engine::Instantiate(menuManager);
    cameraGo->GetComponent<FPSCamera>()->moveCam = &moveCam;
    //go->GetComponent<Menu>()->camera_ptr = cameraGo->GetComponent<Camera>();
    //go->GetComponent<Menu>()->selectedGO = floor;
 
}

// some cubes with physics
void PhysTest() {

    GameObject cube;
    auto* r = cube.AddComponent<Renderer>();
    r->mesh_ptr = Resources::GetMesh("unitCube");
    r->texture_ptr = Resources::GetTexture("cat.png");
    cube.AddComponent<Collider>();
    cube.AddComponent<RigidBody>();
    cube.GetComponent<Transform>()->position.y = 3;

    auto* go = Engine::Instantiate(cube);

    Time::timeScale = 0.1f;
    Physics::gravity = { 0,-0.0,0 };
}





// the game must provide its own main, and must follow this structure
int main(int argc, char* argv[]){
    
    Engine::Initialize();

    ///////////////////////////////////////////////////////////
    // Here is where you put your own code to add GameObjects to Scene
    StandardMap();
    PhysTest();


    ///////////////////////////////////////////////////////////

    Engine::Run();

    Engine::Terminate();

    return 0;
}




