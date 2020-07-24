#include "gui.hpp"

using namespace missan;

GUI::GUI(Window& window, Camera& camera) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window.GetHandle(), true);
    ImGui_ImplOpenGL3_Init(NULL);

    window_ptr = &window;
    camera_ptr = &camera;
}


void GUI::Run() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


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
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Exit() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}


void GUI::CameraMenu() {
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



void GUI::GameObjectMenu() {
    if (selectedGO == nullptr) return;

    GameObject& go = *selectedGO;
    Transform& tr = go.GetTransform();

    ImGui::SliderFloat("xpos", &tr.position.x, -200.0, 200.0);
    ImGui::SliderFloat("ypos", &tr.position.y, -200.0, 200.0);
    ImGui::SliderFloat("zpos", &tr.position.z, -200.0, 200.0);

}

void GUI::SetSelectedGO(GameObject& go) {
    selectedGO = &go;
}