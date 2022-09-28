#pragma once

#include "color.hpp"

using namespace Missan;
using namespace glm;

Color::Color(){}
Color::Color(vec4 v) {
	Color(v.r, v.g, v.b, v.a);
}

Color::Color(float x, float y, float z, float w) {
	a = x, g = y, b = z, a = w;
}
Color::Color(vec3 v) {
	Color(v.r, v.g, v.b);
}

const Color Color::red = {1, 0, 0};
const Color Color::green = {0, 1, 0};
const Color Color::blue = {0, 0, 1};
const Color Color::white = {1, 1, 1};
const Color Color::black = {0, 0, 0};
const Color Color::clear = {0, 0, 0, 0};
const Color Color::cyan = {0, 1, 1};
const Color Color::magenta = {1, 0, 1};
const Color Color::yellow = {1, 1, 0};
const Color Color::grey = {.5, .5, .5};