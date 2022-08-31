#include "window.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <stdlib.h>

#include "internal.hpp"

using namespace Missan;
using namespace std;

static GLFWwindow* window = nullptr;
static int w = 960;
static int h = 720;
static float ar = 0;
const string title = "Missan 3D";

void glfwErrorCallback(int error, const char* desc) {
    cout << "GLFW Error " << error << ": " << desc << endl;
}


const int& Window::width = w;
const int& Window::height = h;
const float& Window::aspectRatio = ar;

GLFWwindow* WindowInitialize() {
    ar = (float)w / h;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        cout << "glfwInit() failed\n";
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
    if (!window) {
        glfwTerminate();
        cout << "glfwCreateWindow() failed\n";
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int glewState = glewInit();
    if (glewState != GLEW_OK) {
        cout << "GLEW Error: " << glewGetErrorString(glewState) << endl;
        exit(EXIT_FAILURE);
    }

    cout << glGetString(GL_VERSION) << endl;

    return window;
}

void Window::SetIsCursorVisible(bool isVisible) {
    if (isVisible) glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    else glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

