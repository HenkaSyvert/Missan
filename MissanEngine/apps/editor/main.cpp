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

void MakeSphere() {
    GameObject g;
    g.AddComponent<Transform>();
    auto* r = g.AddComponent<Renderer>();
    r->mesh = new Mesh(Resources::GenerateUvSphere(20, 20));
    r->material = new Material();
    r->material->texture = Resources::GetTexture("resources/textures/blank.png");
    g.name = "sphere";
    g.AddComponent<Collider>();
    GameObject::Instantiate(&g);

    auto* g2 = GameObject::Instantiate(&g);
    g2->GetComponent<Transform>()->position.x += 2;
}

int main(){
    
    Engine::Initialize();

    MakeEditor();
    //PlaceSomeCubes();
    MakeLight();
    MakeSphere();

    Engine::Run();

    return 0;
}




