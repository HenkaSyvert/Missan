#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace Missan;

// PRIVATE
namespace {

    GLFWwindow* windowHandle = nullptr;
    int   width_       = 0;
    int   height_      = 0;
    float aspectRatio_ = 0;

    void glfwErrorCallback(int error, const char* desc) {
        std::cout << "GLFW Error " << error << ": " << desc << std::endl;
    }

}


// PUBLIC
const int&   Window::width       = width_;
const int&   Window::height      = height_;
const float& Window::aspectRatio = aspectRatio_;

void Window::Initialize(int width, int height, const std::string& title) {
	width_ = width;
	height_ = height;
    aspectRatio_ = (float)width_ / height_;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        std::cout << "glfwInit() failed\n";
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(width, height, title.c_str(), NULL/*glfwGetPrimaryMonitor() // fullscreen*/, NULL);
    if (!windowHandle) {
        glfwTerminate();
        std::cout << "glfwCreateWindow() failed\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(1);

    int glewState = glewInit();
    if (glewState != GLEW_OK) {
        std::cout << "GLEW Error: " << glewGetErrorString(glewState) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
}

void Window::SetIsCursorVisible(bool isVisible) {
    if (isVisible) glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}



GLFWwindow* Window::GetHandle() {
    return windowHandle;
}

