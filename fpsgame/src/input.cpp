#include "input.h"

using namespace missan;

Input::Input(Window& window) {
	window_ptr = &window;
	glfwGetCursorPos(window_ptr->GetHandle(), &mousePos.x, &mousePos.y);
	Update();
}

bool Input::IsKeyPressed(int keycode) {
	int state = glfwGetKey(window_ptr->GetHandle(), keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

glm::dvec2 Input::GetMousePos() {
	return mousePos;
}

glm::dvec2 Input::GetMouseDelta() {
	return mouseDelta;
}

double Input::GetTime() {
	return time;
}

double Input::GetDeltaTime() {
	return deltaTime;
}

void Input::Update() {
	deltaTime = glfwGetTime() - time;
	time = glfwGetTime();
	glm::dvec2 old = mousePos;
	glfwGetCursorPos(window_ptr->GetHandle(), &mousePos.x, &mousePos.y);
	mouseDelta = mousePos - old;
	glfwPollEvents();
}