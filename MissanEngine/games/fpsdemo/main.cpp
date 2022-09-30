#include "missan.hpp"

#include "editor.hpp"

using namespace Missan;


void MakeEditor() {

    GameObject editor;
    editor.AddComponent<Transform>();
    editor.AddComponent<Camera>();
    editor.AddComponent<Editor>();

    auto* g = GameObject::Instantiate(editor);
    Camera::main = g->GetComponent<Camera>();




    GameObject cube;
    cube.AddComponent<Transform>();
    auto* r = cube.AddComponent<Renderer>();
    r->material = new Material();
    r->material->texture = Resources::GetTexture("resources/textures/stone2.png");
    r->mesh = Resources::GetMesh("resources/meshes/cube.mesh");
    g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {0, 0, -2};
    g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {-2, 0, 0};
    g = GameObject::Instantiate(cube);
    g->GetComponent<Transform>()->position += {0, 0, 2};

}



int main(){
    
    Engine::Initialize();

    MakeEditor();


    Engine::Run();

    return 0;
}




