// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

#include "scripts/fpscam.hpp"
#include "scripts/FloatScript.hpp"
#include "scripts/menu.hpp"

using namespace missan;


Scene* StandardMap(Camera& camera) {

    Scene* scene_ptr = new Scene;
    Scene& scene = *scene_ptr;



    // MESHES & TEXTURES
    Mesh& unitCube = *Resources::GetMesh("unitCube");
    Mesh& unitPlane = *Resources::GetMesh("unitPlane");

    Texture& brickTexture = *Resources::GetTexture("brickwall.png");
    Texture& stoneTexture = *Resources::GetTexture("stonefloor.png");



    // GAME OBJECTS
    // 10x2 wall
    GameObject wallPrefab(unitPlane, brickTexture);
    wallPrefab.GetTransform().scale = { 10,2,1 };
    wallPrefab.AddComponent<FloatScript>();

    // 10x10 floor
    GameObject floorPrefab(unitPlane, stoneTexture);
    floorPrefab.GetTransform().scale = { 10,10,1 };
    floorPrefab.GetTransform().rotationDeg = { 90,0,0 };



    // INSTANTIATIONS
    GameObject& ref1 = scene.Instantiate(floorPrefab);
    ref1.GetTransform().position.y = -1;
    for (int i = 0; i < 3; i++) {
        GameObject& ref1 = scene.Instantiate(wallPrefab);
        ref1.GetTransform().position = { 5 * cos(i*3.1415 * 0.5),0,5 * sin(i*3.1415 * 0.5) };
        ref1.GetTransform().rotationDeg = { 0,90 + 90 * i,0 };
    }

    GameObject menuManager;
    GameObject& mm = scene.Instantiate(menuManager);
    mm.AddComponent<Menu>();
    mm.GetComponent<Menu>()->camera_ptr = &camera;
    mm.GetComponent<Menu>()->selectedGO = scene.gameObjects[0];

    // No idea why, but camera MUST be instantiated last..
    GameObject camGO;
    GameObject& ref = scene.Instantiate(camGO);
    ref.AddComponent<FPSCamera>();
    ref.GetComponent<FPSCamera>()->moveCam = &mm.GetComponent<Menu>()->moveCam;
    camera.BindToTransform(ref.GetTransform());

    return scene_ptr;

}


// MAIN LOOP STUFF
bool renderColliders = true;
void RenderScene(Renderer& renderer, Scene& scene) {
    renderer.Prepare();
    renderer.Render(scene);
    if (renderColliders) {
        for (auto* g : scene.gameObjects) {
            if (g->GetCollider().IsEnabled())
                renderer.RenderCollider(g->GetCollider());
        }
    }
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

    ShaderProgram standardShader("standard.vs", "standard.fs");
    Camera camera;
    Renderer renderer(standardShader, camera);



    Scene& scene = *StandardMap(camera);
    Engine::SetActiveScene(scene);

    

    while (!glfwWindowShouldClose(Window::GetHandle())) {
        
        
        RenderScene(renderer, scene);
        
        Engine::Run();
        

        glfwSwapBuffers(Window::GetHandle());
    }

    // CLEANUP
    Engine::Terminate();
    glfwTerminate();

    return 0;

}




