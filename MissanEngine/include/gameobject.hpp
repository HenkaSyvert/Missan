#pragma once

#include <glm/glm.hpp>

#include "components/transform.hpp"
#include "mesh.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "input.hpp"
#include "collider.hpp"

#include <vector>
#include <typeinfo>
#include "components/component.hpp"

namespace missan {

	class GameObject {

		// TODO, cleanup component memory allocation

	private:
		Transform transform;
		Mesh*    mesh_ptr    = nullptr;
		Texture* texture_ptr = nullptr;		
		Collider collider;


	public:
		GameObject();
		~GameObject();
		GameObject(GameObject& copy);
		GameObject(Mesh& mesh, Texture& texture);
		

		Transform& GetTransform();
		
		Mesh& GetMesh() const ;
		void SetMesh(Mesh& mesh);

		Texture& GetTexture() const;
		void SetTexture(Texture& texture);
		void Update();

		Collider& GetCollider();


		// component stuff
		std::vector<class Component*> components;
		template <class T> 
		void AddComponent() {
			components.push_back(new T());
			components.back()->AttachToGameObject(*this);
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