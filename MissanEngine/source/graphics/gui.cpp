#include "internal.hpp"

#include "graphics/window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "ecs.hpp"

using namespace Missan;
using namespace ImGui;

void GuiInitialize(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    CreateContext();
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(NULL);
}

void GuiUpdate() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    NewFrame();

    for (auto* g : GameObject::gameObjects) g->OnGui();

    Render();
    ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
}
    
void GuiTerminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
}

