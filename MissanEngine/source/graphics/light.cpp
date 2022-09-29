#include "graphics/light.hpp"

using namespace Missan;
using namespace ImGui;


void Light::DisplayInInspector() {
	Text("Light");
	ColorEdit4("ambient", (float*)&ambient);
	ColorEdit4("diffuse", (float*)&diffuse);
	ColorEdit4("specular", (float*)&specular);
}