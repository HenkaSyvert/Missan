#include "renderer.hpp"

#include "graphics.hpp"

#include <iostream>

using namespace missan;

// PUBLIC

void Renderer::OnRender() {
    Graphics::Draw(this);
}

