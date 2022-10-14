#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "objectarray.hpp"
#include "rawarray.hpp"

#define MISSAN_DEBUG_ECS 0

namespace Missan {

	namespace ECS {

		extern std::vector<ObjectArrayBase*> arrays;

		// Unique ID per component type
		extern size_t numberOfTypes;
		template<class T>
		size_t GetTypeId() {
			static const size_t typeId = numberOfTypes++;
			if (MISSAN_DEBUG_ECS) std::cout
				<< "GetTypeId<" << typeid(T).name()
				<< ">():\n\ttypeId = " << typeId
				<< "\n\tnumberOfTypes = " << numberOfTypes << std::endl;
			if (typeId >= arrays.size()) {
				if (MISSAN_DEBUG_ECS) std::cout << "\tarrays.push_back()\n";
				arrays.push_back(new ObjectArray<T>());
			}
			return typeId;
		}

		// from which index all ECS are types of components (as opposed to assets and gameobject). 
		extern size_t componentOffset;


		// convenience function to not having to cast every time. 
		template<class T>
		ObjectArray<T>& GetArray() {
			return *(ObjectArray<T>*)arrays[GetTypeId<T>()];
		}





		template<class T>
		T* Get(size_t id) {
			return GetArray<T>().Get(id);
		}

		template<class T>
		T* Get(const std::string& name) {
			return GetArray<T>().Get(name);
		}

		template<class T>
		void Add(size_t id) {
			GetArray<T>().Add(id);
		}

		template<class T>
		void Remove(size_t id) {
			GetArray<T>().Remove(id);
		}

		template<class T>
		RawArray<T> AsRawArray() {
			return GetArray<T>().AsRawArray();
		}


		template<class T>
		RawArray<T*> GetAll(size_t id) {
			std::vector<T*> entries;
			for (auto& table : arrays) if (table->Get(id)) entries.push_back((T*)table->Get(id));			
			return RawArray<T*>(entries.data(), entries.size(), true);
		}

		void RemoveAll(size_t id);

		void Copy(size_t destinationId, size_t sourceId);


	};

}