#pragma once

#include <vector>

#include "object.hpp"
#include "objectarray.hpp"
#include "rawarray.hpp"
#include "idtypes.hpp"


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
		// Since typeId indexes into arrays, unknown types
		// are also immediately registered when this func is called. 
		template<class T>
		inline TypeId GetTypeId() {
			static const TypeId typeId = arrays.size();
			if (typeId >= arrays.size()) {
				arrays.push_back(new ObjectArray<T>());
			}
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



		InstanceId NewByTypeId(TypeId typeId, void* object = nullptr);

		template<class T>
		inline InstanceId New(T* object = nullptr) {
			return NewByTypeId(GetTypeId<T>(), object);
		}



		void* GetByTypeId(TypeId typeId, InstanceId instanceId);

		template<class T>
		inline T* Get(InstanceId instanceId) {
			return (T*)GetByTypeId(GetTypeId<T>(), instanceId);
		}



		void DeleteByTypeId(TypeId typeId, InstanceId instanceId);

		template<class T>
		inline void Delete(InstanceId instanceId) {
			DeleteByTypeId(GetTypeId<T>(), instanceId);
		}

	}

}