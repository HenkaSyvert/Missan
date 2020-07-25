#pragma once

#include "components/camera.hpp"// maybe temp
#include "shaderprogram.hpp"	// temp
#include "gameobject.hpp"		//temp
#include "components/renderer.hpp"


namespace missan {

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