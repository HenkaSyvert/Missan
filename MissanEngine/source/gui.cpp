#include "gui.hpp"

#include "window.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

using namespace Missan;
using namespace ImGui;

void GUI::Initialize() {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window::GetHandle(), true);
    ImGui_ImplOpenGL3_Init(NULL);
}

void GUI::Begin() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();
}
    
void GUI::End(){
    Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void GUI::Terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}


