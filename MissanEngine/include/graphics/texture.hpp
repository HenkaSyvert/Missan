#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include "inspectable.hpp"

namespace Missan {

	///
	/// A Texture is a 2D image that is rendered onto the surfaces of a Mesh. 
	class Texture : public Inspectable {

	public:

		///
		/// The Texture ID used by OpenGL to identify this Texture. 
		GLuint id;

		///
		/// The width (in pixels) of this Texture. 
		int width;

		/// 
		/// The height (in pixels) of this Texture. 
		int height;

		///
		/// The number of channels this Texture has. 
		/// TODO: i.e. wheter it is RGB or RGBA. Currently only supports rgba. 
		int channels;

		// applies to all texture coords
		enum class WrapMode {
			Repeat = GL_REPEAT,
			MirroredRepeat = GL_MIRRORED_REPEAT,
			ClampToEdge = GL_CLAMP_TO_EDGE,
			ClampToBorder = GL_CLAMP_TO_BORDER
		};
		WrapMode wrapMode();
		void wrapMode(WrapMode wm);

		// applies to both magnifying and minifying
		enum class FilterMode {
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR
		};
		FilterMode filterMode();
		void filterMode(FilterMode fm);

		void DisplayInInspector();

		Texture(const std::string& fileName, WrapMode wm = WrapMode::Repeat, FilterMode fm = FilterMode::Linear);


	private:
		WrapMode _wrapMode;
		FilterMode _filterMode;

	};


}