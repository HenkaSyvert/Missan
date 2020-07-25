#pragma once

#include "missan.hpp"

using namespace missan;


class Menu : public Component {

public:
    Camera* camera_ptr;
    GameObject* selectedGO;

private:

    enum MENU_STATE { CAMERA, GAME_OBJECT } menuState;
    
    void CameraMenu() {
        Camera& cam = *camera_ptr;
        float fov = cam.GetFOV();
        float nearz = cam.GetNearZ();
        float farz = cam.GetFarZ();
        float ap = cam.GetAspectRatio();

        ImGui::SliderFloat("FOV", &fov, 0.1f, 179.9f);
        ImGui::SliderFloat("NearZ", &nearz, 0.01f, farz);
        ImGui::SliderFloat("FarZ", &farz, nearz, 100.0f);
        ImGui::SliderFloat("AspectRatio", &ap, 0.01f, 10.0f);

        if (ImGui::Button("Restore Defaults")) {
            //cam.RestoreDefaults();
        }
        else {
            cam.SetFOV(fov);
            cam.SetNearZ(nearz);
            cam.SetFarZ(farz);
            cam.SetAspectRatio(ap);
        }
    }

    void GameObjectMenu() {
        if (selectedGO == nullptr) return;

        GameObject& go = *selectedGO;
        Transform& tr = go.GetTransform();

        ImGui::SliderFloat("xpos", &tr.position.x, -200.0, 200.0);
        ImGui::SliderFloat("ypos", &tr.position.y, -200.0, 200.0);
        ImGui::SliderFloat("zpos", &tr.position.z, -200.0, 200.0);

    }

    void MainMenu() {
        ImGui::Begin("Menu");
        ImGui::Text("press E to show/hide cursor");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        if (ImGui::Button("Camera")) menuState = CAMERA;
        if (ImGui::Button("GameObject")) menuState = GAME_OBJECT;
        switch (menuState) {
        case CAMERA:        CameraMenu();       break;
        case GAME_OBJECT:   GameObjectMenu();   break;
        default:                                break;
        }
        ImGui::End();
    }


public:
    Menu* Clone() const { return new Menu(*this); }   // necessary for deep-cloning

    void OnGUI() {
        MainMenu();
    }



};

