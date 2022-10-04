#pragma once

#include "component.hpp"
#include "ecs.hpp"

#include <vector>
#include <typeinfo>
#include <string>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject {

	public:

		const size_t& id = _id;
		std::string name;

		/// 
		/// Creates new GameObject
		GameObject();

		/// 
		/// Deletes GameObject and all attached Components
		~GameObject();

		/// 
		/// Creates new instances of copy's Components and attaches them to the new GameObject
		GameObject(GameObject& copy);	

		/// 
		/// Adds Component of type T, attaches it, and returns pointer
		template <class T> inline T* AddComponent() {
			T* component = ECS::AddComponent<T>(id);
			components.push_back(component);
			return component;
		}	

		/// 
		/// Returns pointer to Component of type T if found, else nullptr
		template <class T> inline T* GetComponent() {
			for (Component* c : components)
				if (typeid(T) == typeid(*c))
					return (T*)c;
			return nullptr;
		}
		
		/// 
		/// Removes Component
		template <class T> inline void RemoveComponent() {
			ECS::RemoveComponent<T>(id);
		}
		
		/// 
		/// Instantiates a copy of original in the active Scene, and returns pointer to the copy
		static GameObject* Instantiate(GameObject& original);

		///
		/// Destroys gameObject
		static void Destroy(GameObject* gameObject);


		std::vector<class Component*> components;


	private:
		size_t _id;
	};

}