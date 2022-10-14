#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "object.hpp"
#include "objectarray.hpp"
#include "rawarray.hpp"

#define MISSAN_DEBUG_MEMORY 0

namespace Missan {

	namespace Memory {

		extern std::vector<ObjectArrayBase*> arrays;

		// Unique ID per component type
		extern size_t numberOfTypes;
		template<class T>
		inline size_t GetTypeId() {
			static const size_t typeId = numberOfTypes++;
			if (MISSAN_DEBUG_MEMORY) std::cout
				<< "GetTypeId<" << typeid(T).name()
				<< ">():\n\ttypeId = " << typeId
				<< "\n\tnumberOfTypes = " << numberOfTypes << std::endl;
			if (typeId >= arrays.size()) {
				if (MISSAN_DEBUG_MEMORY) std::cout << "\tarrays.push_back()\n";
				arrays.push_back(new ObjectArray<T>());
			}
			return typeId;
		}

		// convenience function to not having to cast every time. 
		template<class T>
		inline ObjectArray<T>& GetArray() {
			return *(ObjectArray<T>*)arrays[GetTypeId<T>()];
		}

		template<class T>
		inline T* Get(Object::IdType id) {
			return GetArray<T>().Get(id);
		}

		template<class T>
		inline void Add(Object::IdType id) {
			GetArray<T>().Add(id);
		}

		template<class T>
		inline void Remove(Object::IdType id) {
			GetArray<T>().Remove(id);
		}

		template<class T>
		inline RawArray<T> AsRawArray() {
			return GetArray<T>().AsRawArray();
		}




		// TODO: move to ECS
		// from which index all ECS are types of components (as opposed to assets and gameobject). 
		extern size_t componentOffset;

		// TODO: move to resources
		template<class T>
		inline T* Get(const std::string& name) {
			return GetArray<T>().Get(name);
		}

		// TODO: move to ECS
		template<class T>
		RawArray<T*> GetAll(Object::IdType id) {
			std::vector<T*> entries;
			for (auto& table : arrays) if (table->Get(id)) entries.push_back((T*)table->Get(id));			
			return RawArray<T*>(entries.data(), entries.size(), true);
		}

		// TODO: move to ECS?
		void RemoveAll(size_t id);

		// TODO: move to ECS
		void Copy(Object::IdType destinationId, Object::IdType sourceId);


	};

}