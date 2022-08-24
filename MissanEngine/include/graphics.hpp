#pragma once

#include "camera.hpp"
#include "shaderprogram.hpp"
#include "gameobject.hpp"
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