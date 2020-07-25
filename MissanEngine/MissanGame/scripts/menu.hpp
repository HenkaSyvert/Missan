#pragma once

#include "missan.hpp"

using namespace missan;

class Menu : public Component {

public:
    Camera* camera_ptr;
    GameObject* selectedGO;
    bool moveCam = false;

private:

    enum MENU_STATE { 
        CAMERA, 
        GAME_OBJECT 
    } menuState;
    
    

    float keyCoolDown = 0.2f, keyTimer = 0;
    bool afterCoolDown = true;

    void CameraMenu() {
        Camera& cam = *camera_ptr;

        ImGui::SliderFloat("FOV", &cam.fieldOfViewDeg, 0.1f, 179.9f);
        ImGui::SliderFloat("NearZ", &cam.nearClipPlane, 0.01f, cam.farClipPlane);
        ImGui::SliderFloat("FarZ", &cam.farClipPlane, cam.nearClipPlane, 100.0f);
        ImGui::SliderFloat("AspectRatio", &cam.aspectRatio, 0.01f, 10.0f);

        if (ImGui::Button("Restore Defaults"))
            cam.Restore();
        
    }

    void GameObjectMenu() {
        if (selectedGO == nullptr) return;

        GameObject& go = *selectedGO;
        Transform& tr = *go.GetComponent<Transform>();

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

    void Update() {
        if (!afterCoolDown) {
            keyTimer += Time::deltaTime;
            if (keyTimer > keyCoolDown) {
                afterCoolDown = true;
                keyTimer = 0;
            }
        }

        if (afterCoolDown && Input::IsKeyPressed(GLFW_KEY_E)) {
            afterCoolDown = false;
            moveCam = !moveCam;
            Window::SetIsCursorVisible(!moveCam);
        }
    }

    void OnGUI() {
        MainMenu();
    }



};

