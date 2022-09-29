#pragma once

#include "graphics/renderer.hpp"

using namespace Missan;
using namespace ImGui;
using namespace std;

void Renderer::DisplayInInspector() {
	Text("Renderer");
	if (material) material->DisplayInInspector();
}