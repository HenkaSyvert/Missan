#pragma once

#include "inspectable.hpp"
#include "util/packedassociativearray.hpp"
#include "util/rawarray.hpp"

#include <string>
#include <typeinfo>
#include <vector>

namespace Missan {


	/// Components define behavior of GameObjects. To make a custom script, inherit from Component. 
	/// Override the event functions - here listed in order of execution - in your own scripts. 
	class Component : public Inspectable {
		
	public:
	
		/// 
		/// The GameObject this Component is attached to. 
		size_t gameObjectId;

		///
		/// Called only once for each GameObject, before all other Event functions
		inline virtual void Start() {}

		///
		/// Called when this Collider has begun touching another Collider
		virtual void OnCollisionEnter(size_t otherGameObjectId) {}

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

		template<class T>
		T* GetComponent() { return Component::Get<T>(gameObjectId); }




		template<class T> static RawArray<T> GetRawArray() {
			//std::cout << "get raw componentArray<" << typeid(T).name() << ">\n";
			return GetComponentArray<T>().AsRawArray();
		}

		static RawArray<Component*> GetAttachedComponents(size_t gameObjectId);

		// Create new component and attach to gameobject
		template<class T> static void Add(size_t gameObjectId) {
			//std::cout << "Add componentArray<" << typeid(T).name() << ">[" << gameObjectId << "]\n";
			auto& arr = GetComponentArray<T>();
			arr.Add(gameObjectId);
			auto* comp = arr.Get(gameObjectId);
			comp->gameObjectId = gameObjectId;
			arr.Get(gameObjectId)->Start();
		}

		// remove component from gameobject
		template<class T> static void Remove(size_t gameObjectId) {
			//std::cout << "Remove componentArray<" << typeid(T).name() << ">[" << gameObjectId << "]\n";
			auto& arr = GetComponentArray<T>();
			arr.Get(gameObjectId)->OnDestroy();
			arr.Remove(gameObjectId);
		}


		template<class T> static T* Get(size_t gameObjectId) {
			//std::cout << "Get componentArray<" << typeid(T).name() << ">[" << gameObjectId << "]\n";
			return GetComponentArray<T>().Get(gameObjectId);
		}

		static void Copy(size_t destinationId, size_t sourceId);
		static void Destroy(size_t gameObjectId);

		static void UpdateAll();
		static void LateUpdateAll();
		static void OnGuiAll();

		static std::vector<PackedAssociativeArrayBase*> componentArrays;
	private:

		

		// convenience function to not having to cast every time. 
		template<class T>
		static PackedAssociativeArray<T>& GetComponentArray() {
			return *(PackedAssociativeArray<T>*)componentArrays[GetTypeId<T>()];
		}

		// Unique ID per component type
		static size_t numberOfTypes;
		template<class T>
		static size_t GetTypeId() {
			static const size_t typeId = numberOfTypes++;
			static bool isRegistered = false;
			if (!isRegistered) {
				std::cout << "reg componentArray<" << typeid(T).name() << " : " << typeId << ">\n";
				componentArrays.push_back(new PackedAssociativeArray<T>());
				isRegistered = true;
			}
			return typeId;
		}
	};
}
