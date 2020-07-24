#include "input.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>


using namespace missan;

namespace {

	Window* window_ptr = nullptr;
	glm::dvec2 mousePosition_;
	glm::dvec2 mouseDelta_;

}

// PUBLIC
const glm::dvec2& Input::mousePosition = mousePosition_;
const glm::dvec2& Input::mouseDelta    = mouseDelta_;

void Input::Initialize(Window& windowHandle) {
	window_ptr = &windowHandle;
	glfwGetCursorPos(window_ptr->GetHandle(), &mousePosition_.x, &mousePosition_.y);
	Input::Update();
}

bool Input::IsKeyPressed(int keycode) {
	int state = glfwGetKey(window_ptr->GetHandle(), keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

void Input::Update() {
	glm::dvec2 old = mousePosition_;
	glfwGetCursorPos(window_ptr->GetHandle(), &mousePosition_.x, &mousePosition_.y);
	mouseDelta_ = mousePosition_ - old;
	glfwPollEvents();
}

