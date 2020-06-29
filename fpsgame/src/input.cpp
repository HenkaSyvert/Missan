#include "input.h"

using namespace missan;

Input::Input(GLFWwindow* window) {
	this->window = window;
	GetMousePos();
}

bool Input::IsKeyPressed(int keycode) {
	int state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::dvec2 Input::GetMousePos() {
	glfwGetCursorPos(window, &mousePos[0], &mousePos[1]);
	return mousePos;
}

glm::dvec2 Input::GetMouseDelta() {
	glm::dvec2 old = mousePos;
	GetMousePos();
	return mousePos - old;
}
