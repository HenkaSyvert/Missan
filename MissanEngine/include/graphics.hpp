#pragma once

#include "mesh.hpp"
#include "shaderprogram.hpp"

namespace missan {

	namespace Graphics {

		void Initialize();
		ShaderProgram& GetStandardShader();

		void Draw();
		void Submit(Mesh& mesh);

	}

}