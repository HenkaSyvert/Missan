#include "missan.hpp"

#include "editor.hpp"

using namespace Missan;


void MakeEditor() {

    GameObject editor;
    editor.name = "editor";
    editor.AddComponent<Transform>();
    editor.AddComponent<Camera>();
    editor.AddComponent<Editor>();

    auto* g = GameObject::Instantiate(editor);
    Camera::main = g->GetComponent<Camera>();


}

void PlaceSomeCubes() {
    GameObject cube;
    cube.name = "cube";
    cube.AddComponent<Transform>();
    auto* r = cube.AddComponent<Renderer>();
    r->material = new Material();
    r->material->texture = Resources::GetTexture("resources/textures/stone2.png");
    r->mesh = Resources::GetMesh("resources/meshes/cube.mesh");

    auto* g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {0, 0, -2};
    g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {-2, 0, 0};
    g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {0, 0, 2};

}

void MakeLight() {

    GameObject g;
    g.AddComponent<Light>();
    g.AddComponent<Transform>();
    g.name = "light";

    auto* go = GameObject::Instantiate(g);
    Light::light = go->GetComponent<Light>();

}

int main(){
    
    Engine::Initialize();

    MakeEditor();
    PlaceSomeCubes();
    MakeLight();


    Engine::Run();

    return 0;
}




