#include "window.hpp"

#include <iostream>

using namespace missan;

// PRIVATE

void glfwErrorCallback(int error, const char* desc) {
    std::cout << "GLFW Error " << error << ": " << desc << std::endl;
}


// PUBLIC
Window::Window(int w, int h, std::string name) {
	width = w;
	height = h;
	title = name;

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



GLFWwindow* Window::GetHandle() {
    return windowHandle;
}

float Window::GetAspectRatio() {
    return (float)width / height;
}

int Window::GetWidth() {
    return width;
}

int Window::GetHeight() {
    return height;
}



void Window::SetCursorVisible(bool isVisible) {
    if (isVisible) glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}
