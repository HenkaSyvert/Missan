#include "internal.hpp"

#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "component.hpp"
#include "gameobject.hpp"

using namespace Missan;
using namespace ImGui;

void GuiInitialize(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO& io = GetIO();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);
}

void GuiUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();

    auto& gameObjects = EcsGetGameObjects();
    for (auto* g : gameObjects) for (auto* c : g->components) c->OnGUI();

    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
    

void GuiTerminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}


