#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

#include "gameobject.hpp"

void InputInitialize(GLFWwindow* window);
void InputUpdate();

GLFWwindow* WindowInitialize();

void ResourcesInitialize();
void ResourcesTerminate();

void PhysicsUpdate();

void GuiInitialize(GLFWwindow* window);
void GuiUpdate();
void GuiTerminate();

void GraphicsInitialize();
void GraphicsUpdate();

void EcsComponentsStart();
void EcsComponentsUpdate();
void EcsComponentsLateUpdate();
void EcsGameObjectInstantiate();
void EcsGameObjectDestroy();
std::vector<Missan::GameObject*>& EcsGetGameObjects();
