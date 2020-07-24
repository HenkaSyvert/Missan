// since setting up a library was messy, pretend main.cpp is a separate project using Missan API

#include "missan.hpp"

#include "scripts/fpscam.hpp"

#include <iostream> // debug

using namespace missan;

bool moveCam = false;



class FloatScript : public Component {

private:
    float amp = 1.0f;
    float freq = 5.0f;

public:
    void Update() override {

        Transform& trans = gameObject_ptr->GetTransform();

        trans.position.y = amp * sinf(freq * Time::time);
    }

};



// Scripts
void SinusFloat(GameObject& go) {

    float amp = 1.0f;
    float freq = 5.0f;

    Transform& trans = go.GetTransform();
    float t = Time::time;

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
        for (auto* g : scene.GetGameObjects()) {
            if (g->GetCollider().IsEnabled())
                renderer.RenderCollider(g->GetCollider());
        }
    }
}

void RunScripts(Scene& scene) {
    for (GameObject* go : scene.GetGameObjects())
        go->Update();
}

void CheckCollisions(Scene& scene) {
    for (auto* a : scene.GetGameObjects()) {
        Collider& ca = a->GetCollider();

        for (auto* b : scene.GetGameObjects()) {
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
    
    // INITIALIZATION
    Window window(960, 720, "Missan 3D");
    Input::Initialize(window);
    Resources::Initialize();
    ShaderProgram standardShader("standard.vs", "standard.fs");
    Camera camera(window);
    Renderer renderer(standardShader, camera);
    GUI gui(window, camera);



    // MESHES & TEXTURES
    Mesh& unitCube = *Resources::GetMesh("unitCube");
    Mesh& unitPlane = *Resources::GetMesh("unitPlane");

    Texture& brickTexture = *Resources::GetTexture("brickwall.png");
    Texture& stoneTexture = *Resources::GetTexture("stonefloor.png");


    
    // GAME OBJECTS
    // 10x2 wall
    GameObject wallprefab(unitPlane, brickTexture);
    wallprefab.GetTransform().scale = { 10,2,1 };
    //wallprefab.SetUpdateFunction(SinusFloat);
    wallprefab.AddComponent<FloatScript>();
    
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
    //ref.SetUpdateFunction(FPSCamera);
    ref.AddComponent<FPSCamera>();
    ref.GetComponent<FPSCamera>()->moveCam = &moveCam;
    camera.BindToTransform(ref.GetTransform());
    ref.GetCollider().SetMesh(unitCube);
    ref.GetCollider().Enable(true);
    


    gui.SetSelectedGO(*scene.GetGameObjects()[0]);
    float keyCoolDown = 0.2f, keyTimer = 0;
    bool afterCoolDown = true;
    


    while (!glfwWindowShouldClose(window.GetHandle())) {
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
            window.SetCursorVisible(!moveCam);
        }
        
        
        RenderScene(renderer, scene);
        RunScripts(scene);
        
        for (GameObject* g: scene.GetGameObjects()) {
            for (Component* c : g->components) {
                c->Update();
            }
        }

        CheckCollisions(scene);
           
       
        gui.Run();

        glfwSwapBuffers(window.GetHandle());
    }

    // CLEANUP
    gui.Exit();
    Resources::Terminate();
    glfwTerminate();

    return 0;

}




