#include "missan.hpp"

#include "editor.hpp"

using namespace Missan;


void MakeEditor() {

    size_t editor = GameObject::Instantiate();
    Component::Add<Transform>(editor);
    Component::Add<Camera>(editor);
    Component::Add<Editor>(editor);


}

void PlaceSomeCubes() {

    size_t cube = GameObject::Instantiate();
    Component::Add<Transform>(cube);
    Component::Add<Renderer>(cube);
    auto* r = Component::Get<Renderer>(cube);
    //r->material = new Material();
    //r->material->texture = Resources::Get<Texture>("resources/textures/stone2.png");
    //r->mesh = Resources::Get<Mesh>("resources/meshes/cube.mesh");
    //r->material->shader = Shader::diffuseSpecular;

}

void MakeLight() {

    size_t light = GameObject::Instantiate();
    Component::Add<Transform>(light);
    Component::Add<Light>(light);


}

int main(){
    
    Engine::Initialize();


    MakeEditor();
    PlaceSomeCubes();
    MakeLight();


    Engine::Run();

    return 0;
}




