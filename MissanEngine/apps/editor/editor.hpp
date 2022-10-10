#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace std;
using namespace ImGui;
using namespace glm;

class Editor : public Component {

public:


	GameObject* selected = nullptr;


    void Update() {
        Transform* transform = GetComponent<Transform>();
        HandleCamera(transform);
        HandleMovement(transform);
    }

    void OnGui() {
        ShowDemoWindow();
        EcsWindow();
        MenuBar();
        HierarchyWindow();
        InspectorWindow(selected);
    }

    bool createCube = false;
    void SpawnRandomCube() {
        size_t g = GameObject::CreatePrimitive(GameObject::PrimitiveType::cube);
        return;
        Component::Add<RigidBody>(g);
        auto* rb = GetComponent<RigidBody>();
        rb->mass = 50;
        vec3 dir = {0, 1, 0};
        dir.z += (float)((rand() % 100) / 100.0f);
        rb->AddImpulse(dir, {0, 1, 0});
    }

    void EcsWindow() {
        if (Begin("Entity Component System")) {

            auto& arrs = Component::componentArrays.tables;
            static int selectedArr = 0;
            static int selectedComp = 0;
            {
                Text("Component Arrays");
                BeginChild("left pane", {200, 0}, true);
                for (int i = 0; i < arrs.size(); i++) {
                    auto arr = arrs[i];
                    if (Selectable(arr->typeName.c_str(), selectedArr == i)) {
                        selectedArr = i;
                        selectedComp = 0;
                    }
                }

                EndChild();
            }
            SameLine();

            auto arr = arrs[selectedArr]->AsRawArrayBase();
            {
                BeginChild("mid pane", {200, 0}, true);
                
                for (int i = 0; i < arr.count; i++) {
                    Component* c = (Component*)arr[i];
                    if (Selectable(("[" + to_string((int)c) + "] " + to_string(i) + ": gameObject " + to_string(c->gameObjectId)).c_str(), selectedComp == i)) {
                        selectedComp = i;
                    }
                }

                EndChild();
            }
            SameLine();

            Component* comp = (Component*)arr[selectedComp];
            {
                BeginChild("right pane", {200, 0}, true);
                if (comp) {
                    Text("Game Object ID: %u", comp->gameObjectId);
                    comp->DisplayInInspector();
                }
                EndChild();
            }


            End();
        }
    }

    void MenuBar() {

        if (BeginMainMenuBar()) {
            
            if (BeginMenu("Game Object")) {
                if (BeginMenu("3D Object")) {
                    if (MenuItem("Cube")) SpawnRandomCube();
                    EndMenu();
                }
                EndMenu();
            }
            EndMainMenuBar();
        }
    }

    void HierarchyWindow() {
        if (Begin("Hierarchy")) {
            int i = 0;
            RawArray<GameObject> gs = GameObject::gameObjects.AsRawArray();
            for (size_t j = 0; j < gs.count; j++) {
                GameObject* g = &gs[j];
                if (Selectable((to_string(i++) + ": " + g->name).c_str(), selected == g)) selected = g;
            }
            End();
        }
    }

    void InspectorWindow(GameObject* g) {
        if (Begin("Inspector")) {
            if (!g) {
                Text("no game object selected");
            }
            else {
                RawArray<Component*> comps = Component::GetAttachedComponents(g->id);
                for (int i = 0; i < comps.count; i++)
                    comps[i]->DisplayInInspector();
                
            }
        }
        End();
    }

    void HandleMovement(Transform* transform) {

        float moveSpeed = 5;


        int xAxis = 0, zAxis = 0;
        if (Input::GetKey(Keycode::D)) xAxis += 1;
        if (Input::GetKey(Keycode::A)) xAxis -= 1;
        if (Input::GetKey(Keycode::S)) zAxis -= 1;
        if (Input::GetKey(Keycode::W)) zAxis += 1;

        float dx = (float)xAxis * moveSpeed * Time::deltaTime;
        float dz = (float)zAxis * moveSpeed * Time::deltaTime;

        transform->position += dx * transform->right;
        transform->position += dz * transform->forward;

    }

    void HandleCamera(Transform* transform){
        if (!Input::GetMouseButton(MouseButton::Right)) return;

        float rotationSpeedDeg = 30.0f;
        float pitchConstraint = 89.9f;

        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::deltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::deltaTime;
        transform->rotation.y += dyRot;
        transform->rotation.x = clamp(transform->rotation.x + dxRot, -pitchConstraint, pitchConstraint);
    }

};