#pragma once

#include "inspectable.hpp"

#include <vector>
#include <typeinfo>
#include <string>
#include <iostream>

namespace Missan {

	template<class T>
	class Component;
	class AbstractComponent;

	/// 
	/// Class representing GameObjects in Missan Scenes
	class GameObject {

	public:

		std::string name = "Game Object";
		std::vector<AbstractComponent*> components;

		~GameObject();

		/// 
		/// Adds Component of type T, attaches it, and returns pointer
		template <class T>
		inline T* AddComponent() {
			T* c = new T();
			c->gameObject = this;
			components.push_back(c);
			return c;
		}

		/// 
		/// Returns pointer to Component of type T if found, else nullptr
		template <class T>
		inline T* GetComponent() {
			for (auto* c : components) {
				auto hashseek = typeid(T).hash_code();
				auto hashfound = typeid(*c).hash_code();
				if (hashseek == hashfound)
					return (T*)c;
			}
			return nullptr;
		}



		static std::vector<GameObject*> gameObjects;

		/// 
		/// Instantiates a new GameObject (based on original, if given) and calls Start() at end of frame. 
		static GameObject* Instantiate(GameObject* original = nullptr);

		///
		/// Marks game object for deletion at end of frame. 
		static void Destroy(GameObject* gameObject);


	};


	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class AbstractComponent : public Inspectable {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		GameObject* gameObject = nullptr;

		virtual ~AbstractComponent() {}

		///
		/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider
		inline virtual void OnCollisionEnter(GameObject* other) {}		

		///
		/// Called every frame
		inline virtual void Update() {}

		///
		/// Called every frame, but after all regular Update events
		inline virtual void LateUpdate() {}

		///
		/// Called during GUI rendering
		inline virtual void OnGui() {}
		
		///
		/// Called prior to the GameObject being destroyed
		inline virtual void OnDestroy() {}

		inline virtual void DisplayInInspector() {}



		inline virtual AbstractComponent* Clone() const = 0;
		

	};


	/// 
	/// This uses the "curiously recurring template pattern" (CRTP) so that every class
	/// does not have to provide its own implementation of the clone method, less boiler plate code. 
	/// also, provides a convenient and syntactically appealing way of gathering instances per component class. 
	/// there is a one-to-one correspondence between each subclass T and Component<T>. 
	template<class T>
	class Component : public AbstractComponent {
	public:

		static std::vector<T*> instances;

		Component() {
			instances.push_back((T*)this);
		}

		Component(const Component& original) {
			instances.push_back((T*)this);
		}
		
		virtual ~Component() {
			for (size_t i = 0; i < instances.size(); i++) 
				if (instances[i] == this) 
					instances.erase(instances.begin() + i);
		}

		Component<T>* Clone() const override {
			return (Component<T>*)new T(*(T*)this);
		}

		// needs to be declared virtual to pass along to next subclass (i think?). 
		inline virtual void Start() {}
		inline virtual void OnCollisionEnter(GameObject* other) {}
		inline virtual void Update() {}
		inline virtual void LateUpdate() {}
		inline virtual void OnGui() {}
		inline virtual void OnDestroy() {}
		inline virtual void DisplayInInspector() {}
	};

	template<class T>
	std::vector<T*> Component<T>::instances;
}
