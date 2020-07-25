#include "graphics.hpp"

#include <iostream>

using namespace missan;

namespace {

	ShaderProgram* standardShader_ = nullptr;

}


// PUBLIC
void Graphics::Initialize() {

	standardShader_ = new ShaderProgram("standard.vs", "standard.fs");

}

void Graphics::Draw() {



}

ShaderProgram& Graphics::GetStandardShader() {
	return *standardShader_;
}

