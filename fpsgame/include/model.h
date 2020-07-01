#pragma once

#include "mesh.h"
#include "texture.h"

namespace missan {

	class Model {
	private:
		Mesh* mesh_ptr = nullptr;
		Texture* texture_ptr = nullptr;

	public:
		Model(Mesh& mesh, Texture& texture);
		Model(Mesh& mesh);

		Mesh& GetMesh();
		void SetMesh(Mesh& mesh);

		Texture& GetTexture();
		void SetTexture(Texture& tex);

	};

}