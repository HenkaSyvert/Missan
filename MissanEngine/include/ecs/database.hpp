#pragma once

#include <vector>
#include <string>

#include "packedassociativearray.hpp"
#include "rawarray.hpp"

namespace Missan {

	class Database {


		// convenience function to not having to cast every time. 
		template<class T>
		PackedAssociativeArray<T>& GetArray() {
			return *(PackedAssociativeArray<T>*)tables[GetTypeId<T>()];
		}

		// Unique ID per component type
		size_t numberOfTypes;
		template<class T>
		size_t GetTypeId() {
			static const size_t typeId = numberOfTypes++;
			static bool isRegistered = false;
			if (!isRegistered) {
				tables.push_back(new PackedAssociativeArray<T>());
				isRegistered = true;
			}
			return typeId;
		}



	public:
		std::vector<PackedAssociativeArrayBase*> tables;


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
			for (auto& table : tables) if (table->Get(id)) entries.push_back((T*)table->Get(id));			
			return RawArray<T*>(entries.data(), entries.size(), true);
		}

		void RemoveAll(size_t id);

		void Copy(size_t destinationId, size_t sourceId);


	};

}