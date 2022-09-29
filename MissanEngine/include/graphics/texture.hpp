#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include "inspectable.hpp"

namespace Missan {

	class Texture : public Inspectable {

	public:

		const GLuint& id = _id;
		const int& width = _width;
		const int& height = _height;
		const int& channels = _channels;

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
		GLuint _id;
		int _width;
		int _height;
		int _channels;
		WrapMode _wrapMode;
		FilterMode _filterMode;

	};


}