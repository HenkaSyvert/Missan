#pragma once

#include "missan.hpp"

using namespace missan;

// script that shows a simple menu
class Menu : public Component {

public:

    // Camera to modify
    Camera* camera_ptr;

    // GameObject to modify
    GameObject* selectedGO;

    // Should the cam move? This is an exampe of a script
    // communicating with another script (FPSCamera) on another
    // GameObject
    bool moveCam = false;

private:

    enum MENU_STATE { 
        CAMERA, 
        GAME_OBJECT 
    } menuState;
    
    // to avoid flickering when pressing button
    float keyCoolDown = 0.2f, keyTimer = 0;
    bool afterCoolDown = true;

    // this menu modifies settings on camera
    void CameraMenu() {
        Camera& cam = *camera_ptr;

        ImGui::SliderFloat("FOV", &cam.fieldOfViewDeg, 0.1f, 179.9f);
        ImGui::SliderFloat("NearZ", &cam.nearClipPlane, 0.01f, cam.farClipPlane);
        ImGui::SliderFloat("FarZ", &cam.farClipPlane, cam.nearClipPlane, 100.0f);
        ImGui::SliderFloat("AspectRatio", &cam.aspectRatio, 0.01f, 10.0f);

        if (ImGui::Button("Restore Defaults"))
            cam.Restore();
        
    }

    // this menu allows to change transform of a gameobject
    void GameObjectMenu() {
        if (selectedGO == nullptr) return;

        GameObject& go = *selectedGO;
        Transform& tr = *go.GetComponent<Transform>();

        ImGui::SliderFloat("xpos", &tr.position.x, -200.0, 200.0);
        ImGui::SliderFloat("ypos", &tr.position.y, -200.0, 200.0);
        ImGui::SliderFloat("zpos", &tr.position.z, -200.0, 200.0);

    }

    // the base menu
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



    // currently all Components, and thus all scripts, require and implementation of this method
    Menu* Clone() const { return new Menu(*this); }   // necessary for deep-cloning

};

