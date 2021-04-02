#pragma once

#include "graphics/camera.hpp"			// maybe temp
#include "graphics/shaderprogram.hpp"	// temp
#include "core/gameobject.hpp"			//temp
#include "graphics/renderer.hpp"


namespace Missan {

	///
	/// Graphics functions
	namespace Graphics {

		///
		/// Generates a basic standard shader
		ShaderProgram& GetStandardShader();

		///
		/// Renders a renderer using its mesh and texture
		void Draw(Renderer* renderer);

		///
		/// Sets the camera which renders to the screen. 
		void SetCamera(Camera& camera);



		void Initialize();
		void Prepare();
	}

}