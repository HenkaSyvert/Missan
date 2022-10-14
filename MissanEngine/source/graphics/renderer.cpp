#pragma once

#include "graphics/renderer.hpp"

using namespace Missan;
using namespace ImGui;
using namespace std;

void Renderer::DisplayInInspector() {
	if (CollapsingHeader("Renderer")) {
		if (materialId) Memory::Get<Material>(materialId)->DisplayInInspector();
	}
}