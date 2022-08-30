#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>


namespace Missan {
	class GameObject;
	class Component;
}

void InputInitialize(GLFWwindow* window);
void InputUpdate();

GLFWwindow* WindowInitialize();

void ResourcesTerminate();

void PhysicsUpdate();

void GuiInitialize(GLFWwindow* window);
void GuiUpdate();
void GuiTerminate();

void GraphicsInitialize();
void GraphicsUpdate();

extern std::vector<Missan::Component*> components;

void EcsComponentsStart();
void EcsComponentsUpdate();
void EcsComponentsLateUpdate();
void EcsGameObjectInstantiate();
void EcsGameObjectDestroy();
std::vector<Missan::GameObject*>& EcsGetGameObjects();
template <class T> T* EcsAddComponent() {
	components.push_back(new T());
	return (T*)components.back();
}

void EcsDeleteComponent(Missan::Component* component);