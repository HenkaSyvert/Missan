#pragma once

#include "camera.hpp"			// maybe temp
#include "shaderprogram.hpp"	// temp
#include "gameobject.hpp"			//temp
#include "renderer.hpp"


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