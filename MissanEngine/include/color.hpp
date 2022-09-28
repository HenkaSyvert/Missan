#pragma once

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

namespace Missan {

	class Color {

	public:
		float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;

		static const Color red;
		static const Color green;
		static const Color blue;
		static const Color white;
		static const Color black;
		static const Color clear;
		static const Color cyan;
		static const Color magenta;
		static const Color yellow;
		static const Color grey;

		Color();
		Color(glm::vec4 v);
		Color(glm::vec3 v);
		Color(float r, float g, float b, float a = 1);
		

	};

}