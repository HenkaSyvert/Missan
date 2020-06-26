#pragma once

#include "transform.h"
#include "mesh.h"
#include "texture.h"

namespace missan {

	class GameObject {

	private:
		Transform transform;
		Mesh* mesh_ptr = nullptr;
		Texture* texture_ptr = nullptr;

	public:
		Transform& GetTransform();

		Mesh& GetMesh();
		void SetMesh(Mesh& mesh);

		Texture& GetTexture();
		void SetTexture(Texture& tex);

	};

}