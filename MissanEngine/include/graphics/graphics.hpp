#pragma once

#include "graphics/camera.hpp"// maybe temp
#include "graphics/shaderprogram.hpp"	// temp
#include "core/gameobject.hpp"		//temp
#include "graphics/renderer.hpp"


namespace Missan {

	// should this even be public?
	namespace Graphics {

		// maybe make static member of ShaderProgram?..
		ShaderProgram& GetStandardShader();

		// should this be public?..
		void Draw(Renderer* renderer);

		// temp until several cams are supported
		void SetCamera(Camera& camera);



		// NOT PART OF PUBLIC API ///////////////////////////
		void Initialize();
		void Prepare();
	}

}