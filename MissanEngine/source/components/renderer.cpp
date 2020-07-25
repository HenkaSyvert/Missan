#include "components/renderer.hpp"

#include "graphics/graphics.hpp"

#include <iostream>

using namespace missan;

// PUBLIC

void Renderer::OnRender() {
    Graphics::Draw(this);
}

