#pragma once

#include "missanpch.hpp"

namespace Missan {

	/// 
/// 2D Texture
	class Texture {
	public:
		
		/// 
/// File name
		const std::string fileName;

		/// 
/// In pixels
		const int width = 0; 

		/// 
/// In pixels
		const int height = 0; 

		/// 
/// todo: make relevant
		const int bitsPerPixel = 0;	



		/// 
/// Creates new Texture
		Texture(GLuint newTextureID, const std::string& newFileNameint, int w, int h, int bpp);
		


		/// 
/// NOT PART OF PUBLIC API //////////////////////////
		const GLuint textureID = 0;

		void Bind(int textureSlot = 0);

	};

}