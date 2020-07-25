#pragma once

#include "mesh.hpp"
#include "shaderprogram.hpp"
#include "gameobject.hpp"		//temp
#include "components/camera.hpp"
#include "components/renderer.hpp"


namespace missan {

	class Renderer;

	namespace Graphics {

		void Initialize();
		ShaderProgram& GetStandardShader();

		void Prepare();
		void Draw(Renderer* renderer);

		// temp until several cams are supported
		void SetCamera(Camera& camera);
	}

}