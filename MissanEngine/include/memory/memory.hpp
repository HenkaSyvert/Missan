#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "object.hpp"
#include "objectarray.hpp"
#include "rawarray.hpp"

#define MISSAN_DEBUG_MEMORY 0

namespace Missan {


	/// 
	/// allocates memory in contiguous arrays per class type. 
	/// memory layout may change for cache friendliness, so
	/// access is via unique ID instead of pointer. 
	/// every instance has an unique ID. 
	/// Use this interface to allow Missan to handle objects that
	/// accessed frequently, ie gameObjects, components, assets. 
	namespace Memory {

		extern std::vector<ObjectArrayBase*> arrays;


		// Unique ID per Object subclass
		// used to index index to correct ObjectArray
		// this func automatically registers new types 
		// as soon as an unknown type is called. 
		template<class T>
		inline size_t GetTypeId() {
			static const size_t typeId = arrays.size();
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



		template<class T>
		inline Object::IdType New(T* object = nullptr) {
			return GetArray<T>().Add(object);
		}

		/// 
		/// only use this one if you've already accessed the type array via
		/// one of the templated funcs, otherwise it might not be created yet. 
		inline Object::IdType NewById(size_t arrayIndex, void* object = nullptr) {
			return arrays[arrayIndex]->Add(object);
		}



		template<class T>
		inline T* Get(Object::IdType id) {
			return GetArray<T>().Get(id);
		}

		inline void* GetById(size_t arrayIndex, Object::IdType id) {
			return arrays[arrayIndex]->Get(id);
		}



		template<class T>
		inline void Delete(Object::IdType id) {
			GetArray<T>().Remove(id);
		}

		inline void DeleteById(size_t arrayIndex, Object::IdType id) {
			arrays[arrayIndex]->Remove(id);
		}



	}

}