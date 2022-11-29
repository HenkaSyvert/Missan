#pragma once

#include <glm/vec4.hpp>

namespace Missan {

	///
	/// Defines colors in RGBA format. Each color component is normalized in range [0, 1]. 
	/// Alpha component defines transparancy, with 1 being opaque and 0 being transparent. 
	class Color : public glm::vec4 {

	public:
		
		// to use super class' constructor, so can use initializer lists. 
		using glm::vec4::vec4;
		Color(glm::vec4 v) : glm::vec4(v) {}

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
		static const Color darkGrey;
		static const Color lightGrey;

		// Leaves the alpha value unmodified, because that's what you usually want. 
		inline Color operator*(float f) { return { r * f, g * f, b * f, a }; }

		// Linearly interpolates between Colors a and b by value t. 
		// t should be in range [0, 1] with t = 0 returning a, and
		// t = 1 returning b. 
		inline static Color Lerp(Color a, Color b, float t) {
			return a * (1 - t) + b * t;
		}

	};

}