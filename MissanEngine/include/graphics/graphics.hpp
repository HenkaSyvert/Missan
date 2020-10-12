#pragma once

#include "graphics/camera.hpp"			// maybe temp
#include "graphics/shaderprogram.hpp"	// temp
#include "core/gameobject.hpp"			//temp
#include "graphics/renderer.hpp"


namespace Missan {

	namespace Graphics {

		ShaderProgram& GetStandardShader();

		void Draw(Renderer* renderer);

		void SetCamera(Camera& camera);



		void Initialize();
		void Prepare();
	}

}