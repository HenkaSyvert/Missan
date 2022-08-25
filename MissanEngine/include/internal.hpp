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

void PhysicsUpdate(std::vector<Missan::GameObject*>& gameObjects);

void GuiInitialize(GLFWwindow* window);
void GuiUpdate(std::vector<Missan::GameObject*>& gameObjects);
void GuiTerminate();

void GraphicsInitialize();
void GraphicsUpdate(std::vector<Missan::GameObject*>& gameObjects);