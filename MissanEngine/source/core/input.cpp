#include "core/input.hpp"

using namespace missan;

namespace {

	glm::dvec2 mousePosition_;
	glm::dvec2 mouseDelta_;

}

// PUBLIC
const glm::dvec2& Input::mousePosition = mousePosition_;
const glm::dvec2& Input::mouseDelta    = mouseDelta_;

void Input::Initialize() {
	glfwGetCursorPos(Window::GetHandle(), &mousePosition_.x, &mousePosition_.y);
	Input::Update();
}

bool Input::IsKeyPressed(int keycode) {
	int state = glfwGetKey(Window::GetHandle(), keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

void Input::Update() {
	glm::dvec2 old = mousePosition_;
	glfwGetCursorPos(Window::GetHandle(), &mousePosition_.x, &mousePosition_.y);
	mouseDelta_ = mousePosition_ - old;
	glfwPollEvents();
}

