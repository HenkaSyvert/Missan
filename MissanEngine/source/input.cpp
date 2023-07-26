#pragma once

#include "input.hpp"
#include "internal.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

#include <glm/vec3.hpp>


using namespace Missan;
using namespace std;
using namespace glm;

static GLFWwindow* window = nullptr;

static vec3 _mousePosition;
static vec3 _mouseDelta;
const vec3& Input::mousePosition = _mousePosition;
const vec3& Input::mouseDelta = _mouseDelta;
static bool isButtonDown[5] = {false};
static bool isButtonUp[5] = {false};

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS)
		isButtonDown[button] = true;
	else if (action == GLFW_RELEASE)
		isButtonUp[button] = true;
}

bool Input::GetMouseButton(MouseButton button) {
	return glfwGetMouseButton(window, (int)button) == GLFW_PRESS;
}

bool Input::GetMouseButtonDown(MouseButton button) {
	return isButtonDown[(int)button];
}

bool Input::GetMouseButtonUp(MouseButton button) {
	return isButtonUp[(int)button];
}




static const Keycode keycodes[] = {
	Keycode::Space		    ,
	Keycode::Apostrophe     ,
	Keycode::Comma          ,
	Keycode::Minus          ,
	Keycode::Period         ,
	Keycode::Slash          ,
	Keycode::Alpha0         ,
	Keycode::Alpha1         ,
	Keycode::Alpha2         ,
	Keycode::Alpha3         ,
	Keycode::Alpha4         ,
	Keycode::Alpha5         ,
	Keycode::Alpha6         ,
	Keycode::Alpha7         ,
	Keycode::Alpha8         ,
	Keycode::Alpha9         ,
	Keycode::Semicolon      ,
	Keycode::Equal          ,
	Keycode::A              ,
	Keycode::B              ,
	Keycode::C              ,
	Keycode::D              ,
	Keycode::E              ,
	Keycode::F              ,
	Keycode::G              ,
	Keycode::H              ,
	Keycode::I              ,
	Keycode::J              ,
	Keycode::K              ,
	Keycode::L              ,
	Keycode::M              ,
	Keycode::N              ,
	Keycode::O              ,
	Keycode::P              ,
	Keycode::Q              ,
	Keycode::R              ,
	Keycode::S              ,
	Keycode::T              ,
	Keycode::U              ,
	Keycode::V              ,
	Keycode::W              ,
	Keycode::X              ,
	Keycode::Y              ,
	Keycode::Z              ,
	Keycode::LeftBracket    ,
	Keycode::Backslash      ,
	Keycode::RightBracket   ,
	Keycode::GraveAccent    ,
	Keycode::Escape         ,
	Keycode::Enter          ,
	Keycode::Tab            ,
	Keycode::Backspace      ,
	Keycode::Insert         ,
	Keycode::Delete         ,
	Keycode::Right          ,
	Keycode::Left           ,
	Keycode::Down           ,
	Keycode::Up             ,
	Keycode::PageUp         ,
	Keycode::PageDown       ,
	Keycode::Home           ,
	Keycode::End            ,
	Keycode::CapsLock       ,
	Keycode::ScrollLock     ,
	Keycode::NumLock        ,
	Keycode::Pause          ,
	Keycode::F1             ,
	Keycode::F2             ,
	Keycode::F3             ,
	Keycode::F4             ,
	Keycode::F5             ,
	Keycode::F6             ,
	Keycode::F7             ,
	Keycode::F8             ,
	Keycode::F9             ,
	Keycode::F10            ,
	Keycode::F11            ,
	Keycode::Keypad0        ,
	Keycode::Keypad1        ,
	Keycode::Keypad2        ,
	Keycode::Keypad3        ,
	Keycode::Keypad4        ,
	Keycode::Keypad5        ,
	Keycode::Keypad6        ,
	Keycode::Keypad7        ,
	Keycode::Keypad8        ,
	Keycode::Keypad9        ,
	Keycode::KeypadDecimal  ,
	Keycode::KeypadDivide   ,
	Keycode::KeypadMultiply ,
	Keycode::KeypadSubtract ,
	Keycode::KeypadAdd      ,
	Keycode::KeypadEnter    ,
	Keycode::LeftShift      ,
	Keycode::LeftControl    ,
	Keycode::LeftAlt        ,
	Keycode::LeftSuper      ,
	Keycode::RightShift     ,
	Keycode::RightControl   ,
	Keycode::RightAlt       ,
	Keycode::RightSuper     ,
	Keycode::Menu
};
static unordered_map<Keycode, bool> isKeyDown;
static unordered_map<Keycode, bool> isKeyUp;



static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Keycode k = Keycode(key);
	if (action == GLFW_PRESS)
		isKeyDown[k] = true;
	else if (action == GLFW_RELEASE)
		isKeyUp[k] = true;
}

bool Input::GetKeyDown(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes)
			if (Input::GetKeyDown(k))
				return true;
		return false;
	}
	return isKeyDown[keycode];
}

bool Input::GetKeyUp(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes)
			if (Input::GetKeyUp(k))
				return true;
		return false;
	}
	return isKeyUp[keycode];
}

bool Input::GetKey(Keycode keycode) {
	if (keycode == Keycode::Any) {
		for (auto& k : keycodes)
			if (Input::GetKey(k))
				return true;
		return false;
	}
	return glfwGetKey(window, (int)keycode) == GLFW_PRESS;
}




void InputUpdate() {

	vec3 old = _mousePosition;
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	_mousePosition.x = (float)x;
	_mousePosition.y = (float)y;
	_mouseDelta = _mousePosition - old;

	for (auto& k : isKeyDown) k.second = false;
	for (auto& k : isKeyUp) k.second = false;
	for (auto& b : isButtonDown) b = false;
	for (auto& b : isButtonUp) b = false;

	glfwPollEvents();
}

void InputInitialize(GLFWwindow* w) {
	window = w;

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	_mousePosition.x = (float)x;
	_mousePosition.y = (float)y;

	for (auto k : keycodes) {
		isKeyDown.emplace(k, false);
		isKeyUp.emplace(k, false);
	}

	InputUpdate();
}






