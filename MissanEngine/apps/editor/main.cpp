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
    auto* cube = GameObject::InstantiatePrimitive(GameObject::PrimitiveType::Cube);
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




