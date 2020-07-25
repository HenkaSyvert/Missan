// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

#include "scripts/fpscam.hpp"
#include "scripts/FloatScript.hpp"
#include "scripts/menu.hpp"

using namespace missan;


Scene* StandardMap() {

    Scene* scene_ptr = new Scene;
    Scene& scene = *scene_ptr;



    // MESHES & TEXTURES
    Mesh& unitCube = *Resources::GetMesh("unitCube");
    Mesh& unitPlane = *Resources::GetMesh("unitPlane");

    Texture& brickTexture = *Resources::GetTexture("brickwall.png");
    Texture& stoneTexture = *Resources::GetTexture("stonefloor.png");



    // GAME OBJECTS
    // 10x2 wall
    GameObject wallPrefab;
    auto rend = wallPrefab.AddComponent<Renderer>();
    rend->mesh_ptr = &unitPlane;
    rend->texture_ptr = &brickTexture;
    wallPrefab.GetComponent<Transform>()->scale = { 10,2,1 };
    wallPrefab.AddComponent<FloatScript>();

    // 10x10 floor
    GameObject floorPrefab;
    auto rend2 = floorPrefab.AddComponent<Renderer>();
    rend2->mesh_ptr = &unitPlane;
    rend2->texture_ptr = &stoneTexture;
    floorPrefab.GetComponent<Transform>()->scale = { 10,10,1 };
    floorPrefab.GetComponent<Transform>()->rotationDeg = { 90,0,0 };



    // INSTANTIATIONS
    GameObject& ref1 = scene.Instantiate(floorPrefab);
    ref1.GetComponent<Transform>()->position.y = -1;
    for (int i = 0; i < 3; i++) {
        GameObject& ref1 = scene.Instantiate(wallPrefab);
        ref1.GetComponent<Transform>()->position = { 5 * cos(i*3.1415 * 0.5),0,5 * sin(i*3.1415 * 0.5) };
        ref1.GetComponent<Transform>()->rotationDeg = { 0,90 + 90 * i,0 };
    }

    GameObject camGO;
    GameObject& ref = scene.Instantiate(camGO);
    ref.AddComponent<Camera>();
    Graphics::SetCamera(*ref.GetComponent<Camera>());
    ref.AddComponent<FPSCamera>();
    
    GameObject menuManager;
    GameObject& mm = scene.Instantiate(menuManager);
    mm.AddComponent<Menu>();
    mm.GetComponent<Menu>()->camera_ptr = ref.GetComponent<Camera>();
    mm.GetComponent<Menu>()->selectedGO = scene.gameObjects[0];
    ref.GetComponent<FPSCamera>()->moveCam = &mm.GetComponent<Menu>()->moveCam;

    return scene_ptr;

}



/*
void CheckCollisions(Scene& scene) {
    for (auto* a : scene.gameObjects) {
        Collider& ca = a->GetCollider();

        for (auto* b : scene.gameObjects) {
            if (a == b) continue;
            Collider& cb = b->GetCollider();

            if (ca.OverlapsWith(cb)) {
                // collision happened, do something
                std::cout << "collision detected\n";
            }

        }
    }
}
*/

int main(){
    
    Engine::Initialize();

    Scene& scene = *StandardMap();
    Engine::SetActiveScene(scene);

    Engine::Run();
    Engine::Terminate();
    
    return 0;
}




