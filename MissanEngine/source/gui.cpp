#include "gui.hpp"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <vector>

#include "window.hpp"

using namespace missan;

// PRIVATE
namespace {

    std::vector<void (*)()> submittedFunctions;

}



// PUBLIC
void GUI::Initialize() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(Window::GetHandle(), true);
    ImGui_ImplOpenGL3_Init(NULL);
}

void GUI::Run() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // call the user-made function
    for (void (*func)() : submittedFunctions)
        func();
 
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // should this be done every frame?..
    submittedFunctions.clear();
}

void GUI::Terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::Submit(void (*func)()) {
    submittedFunctions.push_back(func);
}