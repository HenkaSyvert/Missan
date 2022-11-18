#pragma once

#include "inspectable.hpp"
#include "physics/collision.hpp"

#include <vector>
#include <typeinfo>
#include <string>
#include <iostream>

namespace Missan {

	/// 
	/// Class representing GameObjects in Missan scenes. 
	class GameObject : public Inspectable {

	public:

		///
		/// The name of the GameObject. 
		std::string name = "Game Object";

		///
		/// The components attached to this GameObject. There can only be a
		/// single instance per class type attached. 
		std::vector<class AbstractComponent*> components;

		///
		/// The transform of this GameObject. 
		class Transform* transform = nullptr;

		///
		/// Deletes and frees all attached components. 
		~GameObject();

		/// 
		/// Creates new instance of component T and attaches it to the GameObject. 
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





		///
		/// All active GameObjects in the scene, i.e. those that have been instantiated
		/// using GameObject::Instantiate(). GameObjects created on the stack are not 
		/// actually instantiated into the scene. 
		static std::vector<GameObject*> instances;

		/// 
		/// Instantiates a new GameObject calls Start() at end of frame. 
		/// If an original GameObject is provided, its new instances of all
		/// its components are created and attached to the new GameObject. 
		/// The cloned components will be copies of the original components, 
		/// but will have their references to gameObject and transform set
		/// correctly, but all other fields are simply copied as is. 
		static GameObject* Instantiate(GameObject* original = nullptr);

		///
		/// Marks game object for deletion, will call OnDestroy() at end of
		/// current frame, and then delete gameObject and all its attached 
		/// components. 
		static void Destroy(GameObject* gameObject);

		///
		/// Primitive types that can be created with GameObject::InstantiatePrimitive(). 
		enum class PrimitiveType { Cube, Sphere, Plane };

		///
		/// Instantiates a GameObject with a transform, collider, and renderer, 
		/// according to the primitive type. 
		static GameObject* InstantiatePrimitive(PrimitiveType type);




		// These functions are used to neatly call the respective function
		// for all attached components without having to write loops. They are
		// just used by the engine and should not be called in user scripts. 

		///
		/// Calls the Start() event function for all attached components. 
		void Start();

		///
		/// Calls the OnCollisionEnter() event function for all attached components. 
		void OnCollisionEnter(Collision collision);

		///
		/// Calls the OnCollisionStay() event function for all attached components. 
		void OnCollisionStay(Collision collision);

		///
		/// Calls the OnCollisionEnter() event function for all attached components. 
		void OnCollisionExit(Collision collision);

		///
		/// Calls the Update() event function for all attached components. 
		void Update();

		///
		/// Calls the LateUpdate() event function for all attached components. 
		void LateUpdate();

		///
		/// Calls the OnRender() event function for all attached components. 
		void OnRender();

		///
		/// Calls the OnGui() event function for all attached components. 
		void OnGui();

		///
		/// Calls the OnDestroy() event function for all attached components. 
		void OnDestroy();

		///
		/// Calls the DispayInInspector() event function for all attached components. 
		void DisplayInInspector();

	};

	///
	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class AbstractComponent : public Inspectable {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		GameObject* gameObject = nullptr;

		///
		/// The Transform of this GameObject. 
		class Transform* transform = nullptr;

		///
		/// The destructor is virtual so that base pointers can be used to 
		/// delete components while still calling the correct destructor. 
		virtual ~AbstractComponent() {}

		/// 
		/// Returns pointer to Component of type T if found, else nullptr
		template <class T>
		inline T* GetComponent() {
			return gameObject->GetComponent<T>();
		}

		/// 
		/// Creates new instance of component T and attaches it to the GameObject. 
		template <class T>
		inline T* AddComponent() {
			return gameObject->AddComponent<T>();
		}

		///
		/// Only called once, at instantiation or start of simulation. Use this
		/// for initialization. 
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider. 
		/// The Collision information passed is from the perspective of our Collider. 
		inline virtual void OnCollisionEnter(Collision collision) {}		

		///
		/// Called every frame this Collider collides with another Collider. 
		/// The Collision information passed is from the perspective of our Collider. 
		inline virtual void OnCollisionStay(Collision collision) {}

		///
		/// Called on the frame that this Collider has stopped colliding with another Collider. 
		/// The Collision information passed is from the perspective of our Collider. 
		inline virtual void OnCollisionExit(Collision collision) {}

		///
		/// Called once every frame. Bulk of logic goes here. 
		inline virtual void Update() {}

		///
		/// Called once every frame, but after all regular Update events. Use this
		/// for logic that is dependent on being executed last. 
		inline virtual void LateUpdate() {}

		///
		/// Called at the end of the graphics update. 
		inline virtual void OnRender() {}

		///
		/// Called during GUI rendering
		inline virtual void OnGui() {}
		
		///
		/// Called once before the GameObject is destroyed, at the end of
		/// the frame it was marked for destruction. 
		inline virtual void OnDestroy() {}

		///
		/// This is, combined with Component<T>::Clone(), is necessary
		/// to do proper cloning via A
		inline virtual AbstractComponent* Clone() const = 0;
		
	};

	/// 
	/// This uses the "curiously recurring template pattern" (CRTP) so that every class
	/// does not have to provide its own implementation of the Clone method: less boiler plate code. 
	/// Also, provides a convenient and syntactically appealing way of gathering all instances of Component classes. 
	/// There is a one-to-one correspondence between each subclass T and Component<T>. 
	template<class T>
	class Component : public AbstractComponent {

	public:

		///
		/// All instaces of this class. 
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

	};

	template<class T>
	std::vector<T*> Component<T>::instances;
}
