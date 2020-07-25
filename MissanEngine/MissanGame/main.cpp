// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

// load some scripts for demonstration
#include "scripts/fpscam.hpp"
#include "scripts/FloatScript.hpp"
#include "scripts/menu.hpp"

using namespace missan;

// script to make a simple scene
Scene* StandardMap() {

    // create a new scene. we will add some gameobjects to it
    Scene* scene_ptr = new Scene;
    Scene& scene = *scene_ptr;

    // first we must load the meshes and textures we will use
    Mesh& unitCube = *Resources::GetMesh("unitCube");
    Mesh& unitPlane = *Resources::GetMesh("unitPlane");
    Texture& brickTexture = *Resources::GetTexture("brickwall.png");
    Texture& stoneTexture = *Resources::GetTexture("stonefloor.png");



    // now we create some prefabs, i.e. premade template gameobjects
    // which we can later instantiate copies of in the scene
    // first we make floor and wall
    GameObject wallPrefab;
    Renderer* renderer = wallPrefab.AddComponent<Renderer>();
    renderer->mesh_ptr = &unitPlane;
    renderer->texture_ptr = &brickTexture;
    Transform* transform = wallPrefab.GetComponent<Transform>();
    transform->scale = { 10,2,1 };
    wallPrefab.AddComponent<FloatScript>();

    GameObject floorPrefab;
    renderer = floorPrefab.AddComponent<Renderer>();
    renderer->mesh_ptr = &unitPlane;
    renderer->texture_ptr = &stoneTexture;
    transform = floorPrefab.GetComponent<Transform>();
    transform->scale = { 10,10,1 };
    transform->rotationDeg = { 90,0,0 };
    transform->position.y = -1;   

    // a camera is just a gameobject with camera component
    // and a script to make it move like a typical flying fps camera
    GameObject camera;
    camera.AddComponent<Camera>();
    camera.AddComponent<FPSCamera>();

    // a menu is just a gameobject with attached script that overrides
    // the OnGUI() function with ImGui calls. 
    GameObject menuManager;
    menuManager.AddComponent<Menu>();



    // now lets instantiate the objects. Note how we make several walls
    // from 1 original copy, and how we keep the reference to the instantiated
    // object to make changes to it rather than the original
    GameObject* go = &scene.Instantiate(floorPrefab);
    for (int i = 0; i < 3; i++) {
        go = &scene.Instantiate(wallPrefab);
        transform = go->GetComponent<Transform>();
        transform->position = { 5 * cos(i*3.1415 * 0.5),0,5 * sin(i*3.1415 * 0.5) };
        transform->rotationDeg = { 0,90 + 90 * i,0 };
    }

    // and this is somewhat messy, but we need to fix some pointers so they point
    // to gameobjects in the scene rather than the uninstantiated prefabs
    // this will be fixed sometime
    GameObject* cameraGo = &scene.Instantiate(camera);
    Graphics::SetCamera(*cameraGo->GetComponent<Camera>());
    go = &scene.Instantiate(menuManager);
    cameraGo->GetComponent<FPSCamera>()->moveCam = &go->GetComponent<Menu>()->moveCam;
    go->GetComponent<Menu>()->camera_ptr = cameraGo->GetComponent<Camera>();
    go->GetComponent<Menu>()->selectedGO = scene.gameObjects[0];
    
    return scene_ptr;

}


// the game must provide its own main, and must follow this structure
int main(){
    
    Engine::Initialize();

    Scene& scene = *StandardMap();
    Engine::SetActiveScene(scene);

    Engine::Run();
    Engine::Terminate();

    return 0;
}




