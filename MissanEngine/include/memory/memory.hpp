#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <queue>

#include "object.hpp"
#include "objectarray.hpp"
#include "rawarray.hpp"

#define MISSAN_DEBUG_MEMORY 0

namespace Missan {

	// Unique ID per instance
	typedef size_t InstanceId;



	// Unique ID per type
	// also, typeid(T).hash_code() does NOT (apparently) return
	// a unique ID per type per the specificiation, only that
	// same class gets same hash, but 2 classes may share hash. 
	// hence the need for my own TypeId. 
	typedef size_t TypeId;


	/// 
	/// allocates memory in contiguous arrays per class type. 
	/// memory layout may change for cache friendliness, so
	/// access is via unique ID instead of pointer. 
	/// every instance has an unique ID. 
	/// Use this interface to allow Missan to handle objects that
	/// accessed frequently, ie gameObjects, components, assets. 
	namespace Memory {

		// IDs of dead objects, to be reused. 
		extern std::queue<InstanceId> freeIds;

		extern std::vector<ObjectArrayBase*> arrays;

		// generate new unique ID or reuse an old one
		InstanceId GenerateUniqueInstanceId();


		// Unique ID per Object subclass
		// Since typeId indexes into arrays, unknown types
		// are also immediately registered when this func is called. 
		template<class T>
		inline TypeId GetTypeId() {
			static const TypeId typeId = arrays.size();
			if (typeId >= arrays.size()) {
				arrays.push_back(new ObjectArray<T>());
			}
			if (MISSAN_DEBUG_MEMORY) std::cout
				<< "GetTypeId<" << typeid(T).name()
				<< ">():\n\ttypeId = " << typeId
				<< "\n\tarrays.size() = " << arrays.size() << std::endl;
			return typeId;
		}



		template<class T>
		inline ObjectArray<T>& GetArray() {
			return *(ObjectArray<T>*)arrays[GetTypeId<T>()];
		}

		template<class T>
		inline RawArray<T> AsRawArray() {
			return GetArray<T>().AsRawArray();
		}



		/// 
		/// only use this one if you've already accessed the type array via
		/// one of the templated funcs, otherwise it might not be created yet. 
		inline InstanceId NewByTypeId(TypeId typeId, void* object = nullptr) {
			InstanceId id = GenerateUniqueInstanceId();
			arrays[typeId]->Add(id, object);
			return id;
		}

		template<class T>
		inline InstanceId New(T* object = nullptr) {
			return NewByTypeId(GetTypeId<T>(), object);
		}




		inline void* GetByTypeId(TypeId typeId, InstanceId id) {
			return arrays[typeId]->Get(id);
		}

		template<class T>
		inline T* Get(InstanceId id) {
			return GetArray<T>().Get(id);
		}



		inline void DeleteByTypeId(TypeId typeId, InstanceId id) {
			arrays[typeId]->Remove(id);
			freeIds.push(id);
		}

		template<class T>
		inline void Delete(InstanceId id) {
			DeleteByTypeId(GetTypeId<T>(), id);
		}




	}

}