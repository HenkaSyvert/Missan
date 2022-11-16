#include "missan.hpp"

#include "editor.hpp"

using namespace Missan;


void MakeEditor() {

    GameObject editor;
    editor.name = "editor";
    auto* t = editor.AddComponent<Transform>();
    t->position = { 5, 5, 5 };
    t->rotation = { -35, 45, 0 };
    editor.AddComponent<Camera>();
    editor.AddComponent<Editor>();
    GameObject::Instantiate(&editor);

}

void PlaceSomeCubes() {
    auto* cube = GameObject::InstantiatePrimitive(GameObject::PrimitiveType::Cube);
    cube->AddComponent<RigidBody>();
    auto* cube2 = GameObject::Instantiate(cube);
    cube->GetComponent<Transform>()->position.z -= 2;
    cube2->GetComponent<Transform>()->position.z += 2;

}

void MakeLight() {

    GameObject g;
    g.AddComponent<Light>();
    auto* t = g.AddComponent<Transform>();
    g.name = "light";
    t->position.y += 4;
    GameObject::Instantiate(&g);

}

void MakeSphere() {
    auto* cube = GameObject::InstantiatePrimitive(GameObject::PrimitiveType::Sphere);
    cube->AddComponent<RigidBody>();
    auto* cube2 = GameObject::Instantiate(cube);
    cube2->GetComponent<Transform>()->position.x += 3;
}

int main(){
    
    Engine::Initialize();

    MakeEditor();
    PlaceSomeCubes();
    MakeLight();
    MakeSphere();

    Engine::Run();

    return 0;
}




