#pragma once

#include "mesh.hpp"
#include "shaderprogram.hpp"
#include "gameobject.hpp"		//temp
#include "camera.hpp"
#include "renderer.hpp"


namespace missan {

	class Renderer;

	namespace Graphics {

		void Initialize();
		ShaderProgram& GetStandardShader();

		void Prepare();
		void Draw(Renderer* renderer);
		void SetCamera(Camera& camera);		// temp
	}

}