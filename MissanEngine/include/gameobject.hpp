#pragma once

#include <glm/glm.hpp>

#include "transform.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "collider.hpp"

namespace missan {

	class GameObject {

	private:
		Transform transform;
		Mesh*    mesh_ptr    = nullptr;
		Texture* texture_ptr = nullptr;		
		Collider collider;

		void (*UpdateFunc)(GameObject& go, Input& input) = nullptr;

	public:
		GameObject();
		GameObject(Mesh& mesh, Texture& texture);

		Transform& GetTransform();
		
		Mesh& GetMesh();
		void SetMesh(Mesh& mesh);

		Texture& GetTexture();
		void SetTexture(Texture& texture);

		void SetUpdateFunction(void (*func)(GameObject& go, Input& input));
		void Update(Input& input);

		Collider& GetCollider();

	};

}