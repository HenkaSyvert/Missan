#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include "inspectable.hpp"

namespace Missan {

	class Texture : public Inspectable {

	public:

		GLuint id;
		int width;
		int height;
		int channels;

		// applies to all texture coords
		enum class WrapMode {
			repeat = GL_REPEAT,
			mirroredRepeat = GL_MIRRORED_REPEAT,
			clampToEdge = GL_CLAMP_TO_EDGE,
			clampToBorder = GL_CLAMP_TO_BORDER
		};
		WrapMode wrapMode();
		void wrapMode(WrapMode wm);

		// applies to both magnifying and minifying
		enum class FilterMode {
			nearest = GL_NEAREST,
			linear = GL_LINEAR
		};
		FilterMode filterMode();
		void filterMode(FilterMode fm);

		void DisplayInInspector();

		Texture(const std::string& fileName, WrapMode wm = WrapMode::repeat, FilterMode fm = FilterMode::linear);


	private:
		WrapMode _wrapMode;
		FilterMode _filterMode;

	};


}