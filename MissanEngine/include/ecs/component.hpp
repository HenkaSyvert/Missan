#pragma once

#include "inspectable.hpp"
#include "util/packedassociativearray.hpp"

#include <string>
#include <typeinfo>

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
		virtual void OnCollisionEnter(size_t otherGameObjectId){}		

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

		inline virtual void DisplayInInspector(){}




		// Unique ID per component type
		static size_t numberOfTypes;
		template<class T> static size_t GetTypeId() {
			static size_t typeId = numberOfTypes++;
			RegisterById(typeId, sizeof(T));
			return typeId;
		}

		static void RegisterById(size_t componentTypeId, size_t componentSize);


		// get contiguous component array by type
		static PackedAssociativeArray* GetArrayById(size_t componentTypeId);
		template <class T> static PackedAssociativeArray* GetArray() {
			return GetArrayById(GetTypeId<T>());
		}
		template<class T> static T* GetRawArray() {
			return GetArray<T>() ? (T*)GetArray<T>()->data : nullptr;
		}

		// Create new component and attach to gameobject
		static void AddById(size_t gameObjectId, size_t componentTypeId, size_t componentSize, void* component);
		template<class T> static void Add(size_t gameObjectId) {
			T component;
			AddById(gameObjectId, GetTypeId<T>(), sizeof(T), &component);
		}

		// remove component from gameobject
		static void RemoveById(size_t gameObjectId, size_t componentTypeId);
		template<class T> static void Remove(size_t gameObjectId) {
			RemoveById(gameObjectId, GetTypeId<T>());
		}

		static void* GetById(size_t gameObjectId, size_t componentTypeId);
		template<class T> static T* Get(size_t gameObjectId) {
			return (T*)GetById(gameObjectId, GetTypeId<T>());
		}

		// makes new copies of all components attached to source, and attaches them to destination
		static void Copy(size_t destinationId, size_t sourceId);

	};

}
