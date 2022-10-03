#pragma once

#include "missan.hpp"

using namespace Missan;
using namespace std;
using namespace ImGui;
using namespace glm;

class Editor : public Component {

public:


	GameObject* selected = nullptr;
	vector<GameObject*> gos;
    Transform* transform = nullptr;

    void Start() {
        transform = gameObject->GetComponent<Transform>();

    }

    void Update() {
        HandleCamera();
        HandleMovement();
    }

    void OnGui() {
        
        HierarchyWindow();
        InspectorWindow(selected);
        
    }

    void HierarchyWindow() {
        if (Begin("Hierarchy")) {
            gos = EcsGetGameObjects();
            int i = 0;
            for (auto& g : gos)
                if (Selectable((to_string(i++) + ": " + g->name).c_str(), selected == g)) selected = g;
            
            End();
        }
    }

    void InspectorWindow(GameObject* g) {
        if (Begin("Inspector")) {
            if (!g) {
                Text("no game object selected");
            }
            else for (auto& c : g->components) c->DisplayInInspector();
        }
        End();
    }

    void HandleMovement() {

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

    void HandleCamera(){
        if (!Input::GetMouseButton(MouseButton::Right)) return;

        float rotationSpeedDeg = 30.0f;
        float pitchConstraint = 89.9f;

        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::deltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::deltaTime;
        transform->rotation.y += dyRot;
        transform->rotation.x = clamp(transform->rotation.x + dxRot, -pitchConstraint, pitchConstraint);
    }

};