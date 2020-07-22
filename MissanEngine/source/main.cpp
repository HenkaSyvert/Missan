#include "window.hpp"
#include "input.hpp"
#include "loader.hpp"
#include "shaderprogram.hpp"
#include "camera.hpp"
#include "renderer.hpp"
#include "gui.hpp"

#include "mesh.hpp"
#include "texture.hpp"
#include "gameobject.hpp"
#include "scene.hpp"
#include "collider.hpp"

#include <iostream> // debug

using namespace missan;


// Scripts
bool moveCam = false;
void FPSCamera(GameObject& go, Input& input) {

    if (!moveCam) return;

    float moveSpeed = 5.0f;
    float rotationSpeedDeg = 30.0f;
    float pitchConstraint = 89.0f;

    glm::dvec2 mouseDelta = input.GetMouseDelta();
    float deltaTime = (float)input.GetDeltaTime();

    float dyRot = -mouseDelta.x * rotationSpeedDeg * deltaTime;
    float dxRot = -mouseDelta.y * rotationSpeedDeg * deltaTime;

    Transform& transform = go.GetTransform();
    transform.rotationDeg.y += dyRot;
    transform.rotationDeg.x = glm::clamp(transform.rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);
    

    int xAxis = 0, zAxis = 0;
    if (input.IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
    if (input.IsKeyPressed(GLFW_KEY_S)) zAxis += 1;
    if (input.IsKeyPressed(GLFW_KEY_W)) zAxis -= 1;

    float dx = (float)xAxis * moveSpeed * deltaTime;
    float dz = (float)zAxis * moveSpeed * deltaTime;

    transform.position += dx * transform.GetRightVector();
    transform.position += dz * transform.GetBackwardVector();
}

void SinusFloat(GameObject& go, Input& input) {

    float amp = 1.0f;
    float freq = 5.0f;

    Transform& trans = go.GetTransform();
    float t = input.GetTime();

    float sine = amp * sinf(freq * t);
    trans.position.y = sine;

}



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
        for (auto& g : scene.GetGameObjects()) {
            if (g.GetCollider().IsEnabled())
                renderer.RenderCollider(g.GetCollider());
        }
    }
}

void RunScripts(Scene& scene, Input& input) {
    for (GameObject& go : scene.GetGameObjects())
        go.Update(input);
}

void CheckCollisions(Scene& scene) {
    for (auto& a : scene.GetGameObjects()) {
        Collider& ca = a.GetCollider();

        for (auto& b : scene.GetGameObjects()) {
            if (&a == &b) continue;
            Collider& cb = b.GetCollider();

            if (ca.OverlapsWith(cb)) {
                // collision happened, do something
                std::cout << "collision detected\n";
            }

        }
    }
}

int main(){
    
    // INITIALIZATION
    Window window(960, 720, "Missan 3D");
    Input input(window);
    Loader loader;
    ShaderProgram standardShader("standard.vs", "standard.fs");
    Camera camera(window);
    Renderer renderer(standardShader, camera);
    GUI gui(window, camera);



    // MESHES & TEXTURES
    Mesh unitCube  = loader.CreateCubeMesh(1.0f);
    Mesh unitPlane = loader.CreatePlaneMesh(1.0f, 1.0f);

    Texture brickTexture = loader.LoadTexture("brickwall.png");
    Texture stoneTexture = loader.LoadTexture("stonefloor.png");



    // GAME OBJECTS
    // 10x2 wall
    GameObject wallprefab(unitPlane, brickTexture);
    wallprefab.GetTransform().scale = { 10,2,1 };
    wallprefab.SetUpdateFunction(SinusFloat);
    
    // 10x10 floor
    GameObject floorPrefab(unitPlane, stoneTexture);
    floorPrefab.GetTransform().scale = { 10,10,1 };
    floorPrefab.GetTransform().rotationDeg = { 90,0,0 };
    floorPrefab.GetCollider().SetMesh(unitCube);
    floorPrefab.GetCollider().Enable(true);

    Scene scene;
    StandardMap(scene, wallprefab, floorPrefab);

    // No idea why, but camera MUST be instantiated last..
    GameObject camGO;
    GameObject& ref = scene.Instantiate(camGO);
    ref.SetUpdateFunction(FPSCamera);
    camera.BindToTransform(ref.GetTransform());
    ref.GetCollider().SetMesh(unitCube);
    ref.GetCollider().Enable(true);



    gui.SetSelectedGO(scene.GetGameObjects()[0]);
    float keyCoolDown = 0.2f, keyTimer = 0;
    bool afterCoolDown = true;
    


    while (!glfwWindowShouldClose(window.GetHandle())) {
        input.Update();

        
        if (!afterCoolDown) {
            keyTimer += input.GetDeltaTime();
            if (keyTimer > keyCoolDown) {
                afterCoolDown = true;
                keyTimer = 0;
            }
        }

        if (afterCoolDown && input.IsKeyPressed(GLFW_KEY_E)) {
            afterCoolDown = false;
            moveCam = !moveCam;
            window.SetCursorVisible(!moveCam);
        }
        
        
        RenderScene(renderer, scene);
        RunScripts(scene, input);
        CheckCollisions(scene);
           
       
        gui.Run();

        glfwSwapBuffers(window.GetHandle());
    }

    // CLEANUP
    gui.Exit();
    loader.FreeAssets();
    glfwTerminate();

    return 0;

}




