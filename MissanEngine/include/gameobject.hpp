#pragma once

#include <glm/glm.hpp>

#include "transform.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "collider.hpp"

#include <vector>
#include <typeinfo>
#include "component.hpp"

namespace missan {

	class GameObject {

		// TODO, cleanup component memory allocation

	private:
		Transform transform;
		Mesh*    mesh_ptr    = nullptr;
		Texture* texture_ptr = nullptr;		
		Collider collider;

		void (*UpdateFunc)(GameObject& go) = nullptr;


	public:
		GameObject();
		GameObject(Mesh& mesh, Texture& texture);
		GameObject(GameObject& copy);

		Transform& GetTransform();
		
		Mesh& GetMesh();
		void SetMesh(Mesh& mesh);

		Texture& GetTexture();
		void SetTexture(Texture& texture);

		void SetUpdateFunction(void (*func)(GameObject& go));
		void Update();

		Collider& GetCollider();


		// component stuff
		std::vector<class Component*> components;
		template <class T> 
		void AddComponent() {
			components.push_back(new T());
			components.back()->gameObject_ptr = this;
		}
		template <class T>
		T* GetComponent() {
			for (Component* c : components)
				if (typeid(T) == typeid(*c))
					return (T*)c;
			return nullptr;
		}


	};

}