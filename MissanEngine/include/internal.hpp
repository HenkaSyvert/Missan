#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

void InputInitialize(GLFWwindow* window);
void InputUpdate();

GLFWwindow* WindowInitialize();

void PhysicsUpdate();
void DetectCollisions();

void GuiInitialize(GLFWwindow* window);
void GuiUpdate();
void GuiTerminate();

void GraphicsInitialize();
void GraphicsUpdate();

void GameObjectDoDestructions();
void GameObjectDoInstantiations();