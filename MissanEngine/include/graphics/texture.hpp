#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include "inspectable.hpp"
#include "memory/object.hpp"

namespace Missan {

	class Texture : public Object {

	public:

		const GLuint& textureId = _textureId;
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

		static void Load(const std::string& fileName);


	private:
		GLuint _textureId;
		int _width;
		int _height;
		int _channels;
		WrapMode _wrapMode;
		FilterMode _filterMode;

	};


}