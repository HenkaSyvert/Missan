#pragma once

#include "component.hpp"
#include "entitycomponentsystem.hpp"

#include <vector>
#include <typeinfo>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject {

	public:

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
			components.push_back(EcsAddComponent<T>());
			return (T*)components.back();
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
			for (int i = 0; i < components.size(); i++) {
				Component* c = components[i];
				if (typeid(T) == typeid(*c)) {
					EcsDeleteComponent(c);
					components.erase(components.begin() + i);
				}
			}
		}

		/// 
		/// Instantiates a copy of original in the active Scene, and returns pointer to the copy
		static GameObject* Instantiate(GameObject& original);

		///
		/// Destroys gameObject
		static void Destroy(GameObject* gameObject);


		std::vector<class Component*> components;

	};

}