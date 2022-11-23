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

	};

}