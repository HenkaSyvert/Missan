#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stdlib.h>

using namespace Missan;
using namespace std;

static GLFWwindow* windowHandle = nullptr;
static int w = 0;
static int h = 0;
static float ar = 0;

void glfwErrorCallback(int error, const char* desc) {
    cout << "GLFW Error " << error << ": " << desc << endl;
}


const int&   Window::width       = w;
const int&   Window::height      = h;
const float& Window::aspectRatio = ar;

void Window::Initialize(int width, int height, const string& title) {
	w = width;
	h = height;
    ar = (float)w / h;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        cout << "glfwInit() failed\n";
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!windowHandle) {
        glfwTerminate();
        cout << "glfwCreateWindow() failed\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(windowHandle);
    glfwSwapInterval(1);

    int glewState = glewInit();
    if (glewState != GLEW_OK) {
        cout << "GLEW Error: " << glewGetErrorString(glewState) << endl;
        exit(EXIT_FAILURE);
    }

    cout << glGetString(GL_VERSION) << endl;
}

void Window::SetIsCursorVisible(bool isVisible) {
    if (isVisible) glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else glfwSetInputMode(GetHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GLFWwindow* Window::GetHandle() {
    return windowHandle;
}

