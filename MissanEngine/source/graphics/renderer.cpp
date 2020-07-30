#include "graphics/renderer.hpp"

#include "graphics/graphics.hpp"

using namespace Missan;

// dont move this to renderer.hpp, it will creates circular include problems with graphics.hpp
void Renderer::OnRender() { Graphics::Draw(this); }