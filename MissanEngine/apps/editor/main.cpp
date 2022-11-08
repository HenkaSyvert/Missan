#include "missan.hpp"

#include "editor.hpp"

using namespace Missan;


void MakeEditor() {

    GameObject editor;
    editor.name = "editor";
    editor.AddComponent<Transform>();
    editor.AddComponent<Camera>();
    editor.AddComponent<Editor>();
    GameObject::Instantiate(&editor);

}

void PlaceSomeCubes() {
    GameObject cube;
    cube.name = "cube";
    cube.AddComponent<Transform>();
    auto* r = cube.AddComponent<Renderer>();
    r->material = new Material();
    r->material->texture = Resources::GetTexture("resources/textures/stone2.png");
    r->mesh = Resources::GetMesh("resources/meshes/cube.mesh");
    cube.AddComponent<Collider>();
    auto rb = cube.AddComponent<RigidBody>();
    rb->isAffectedByGravity = false;

    GameObject* g = GameObject::Instantiate(&cube);
    g->GetComponent<Transform>()->position.z -= 2;
    g->name += "1";
    g = GameObject::Instantiate(&cube);
    g->GetComponent<Transform>()->position.x -= 2;
    g->name += "2";
    g = GameObject::Instantiate(&cube);
    g->GetComponent<Transform>()->position.z += 2;
    g->name += "3";

}

void MakeLight() {

    GameObject g;
    g.AddComponent<Light>();
    g.AddComponent<Transform>();
    g.name = "light";
    GameObject::Instantiate(&g);

}

int main(){
    
    Engine::Initialize();

    MakeEditor();
    PlaceSomeCubes();
    MakeLight();

    Engine::Run();

    return 0;
}




