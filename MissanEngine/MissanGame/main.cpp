// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

#include "scripts/fpscam.hpp"
#include "scripts/FloatScript.hpp"
#include "scripts/menu.hpp"

#include <iostream> // debug

using namespace missan;

bool moveCam = false;


// MAPS
void StandardMap(Scene& scene, GameObject& wallPrefab, GameObject& floorPrefab) {

    // assumes wall is 10x2, floor is 10x10

    GameObject& ref = scene.Instantiate(floorPrefab);
    ref.GetTransform().position.y = -1;
    for (int i = 0; i < 3; i++) {
        GameObject& ref = scene.Instantiate(wallPrefab);
        ref.GetTransform().position = { 5 * cos(i*3.1415 * 0.5),0,5 * sin(i*3.1415 * 0.5) };
        ref.GetTransform().rotationDeg = { 0,90 + 90 * i,0 };
    }

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

int main(){
    
    Engine::Initialize();

    ShaderProgram standardShader("standard.vs", "standard.fs");
    Camera camera;
    Renderer renderer(standardShader, camera);



    // MESHES & TEXTURES
    Mesh& unitCube = *Resources::GetMesh("unitCube");
    Mesh& unitPlane = *Resources::GetMesh("unitPlane");

    Texture& brickTexture = *Resources::GetTexture("brickwall.png");
    Texture& stoneTexture = *Resources::GetTexture("stonefloor.png");


    
    // GAME OBJECTS
    // 10x2 wall
    GameObject wallprefab(unitPlane, brickTexture);
    wallprefab.GetTransform().scale = { 10,2,1 };
    wallprefab.AddComponent<FloatScript>();
    
    // 10x10 floor
    GameObject floorPrefab(unitPlane, stoneTexture);
    floorPrefab.GetTransform().scale = { 10,10,1 };
    floorPrefab.GetTransform().rotationDeg = { 90,0,0 };
    floorPrefab.GetCollider().SetMesh(unitCube);
    floorPrefab.GetCollider().Enable(true);

    Scene scene;
    StandardMap(scene, wallprefab, floorPrefab);

    GameObject menuManager;
    GameObject& mm = scene.Instantiate(menuManager);
    mm.AddComponent<Menu>();
    mm.GetComponent<Menu>()->camera_ptr = &camera;
    mm.GetComponent<Menu>()->selectedGO = scene.gameObjects[0];

    // No idea why, but camera MUST be instantiated last..
    GameObject camGO;
    GameObject& ref = scene.Instantiate(camGO);
    ref.AddComponent<FPSCamera>();
    ref.GetComponent<FPSCamera>()->moveCam = &moveCam;
    camera.BindToTransform(ref.GetTransform());
    ref.GetCollider().SetMesh(unitCube);
    ref.GetCollider().Enable(true);
    


    float keyCoolDown = 0.2f, keyTimer = 0;
    bool afterCoolDown = true;
    

    while (!glfwWindowShouldClose(Window::GetHandle())) {
        Time::Update();
        Input::Update();

        
        if (!afterCoolDown) {
            keyTimer += Time::deltaTime;
            if (keyTimer > keyCoolDown) {
                afterCoolDown = true;
                keyTimer = 0;
            }
        }

        if (afterCoolDown && Input::IsKeyPressed(GLFW_KEY_E)) {
            afterCoolDown = false;
            moveCam = !moveCam;
            Window::SetIsCursorVisible(!moveCam);
        }
        
        
        RenderScene(renderer, scene);
        
        scene.Update();
        

        CheckCollisions(scene);
           
       
        GUI::Run();

        glfwSwapBuffers(Window::GetHandle());
    }

    // CLEANUP
    GUI::Terminate();
    Resources::Terminate();
    glfwTerminate();

    return 0;

}




