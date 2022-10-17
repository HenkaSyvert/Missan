#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <typeinfo>

#include "rawarray.hpp"
#include "idtypes.hpp"
#include "object.hpp"

#define MISSAN_DEBUG_ARRAY 0

namespace Missan {


	///
	/// Dynamic, contiguous, associative array
	class ObjectArrayBase {
	protected:
		char* data = nullptr;
		std::unordered_map<InstanceId, size_t> idToIndex;
		size_t count = 0;
		const size_t elementSize;
		size_t capacity = 200;


		inline bool IsIdUsed(InstanceId instanceId) const {
			return idToIndex.find(instanceId) != idToIndex.end();
		}

		inline size_t GetOffset(size_t index) const {
			return index * elementSize;
		}

	public:

		const std::string typeName;

		ObjectArrayBase(size_t elementSize, const char* name)
			: elementSize(elementSize), typeName(name)
		{
			data = (char*)malloc(GetOffset(capacity));
		}

		inline RawArrayBase AsRawArrayBase() const {
			return RawArrayBase(data, count, elementSize);
		}

		void Add(InstanceId instanceId, const void* const originalObject) {

			size_t index = count++;
			if (count > capacity) {
				capacity *= 2;
				data = (char*)realloc(data, GetOffset(capacity));
			}

			idToIndex[instanceId] = index;
			
			Object* object = (Object*)&data[GetOffset(index)];
			memcpy(object, originalObject, elementSize);
			object->_instanceId = instanceId;
		}

		void Remove(InstanceId instanceId) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Remove(id = " << instanceId << "):\n";

			if (!IsIdUsed(instanceId)) {
				// intentionally quietly ignore try to remove non existant component, means dont need check prior. 
				if (MISSAN_DEBUG_ARRAY)std::cout << "\terr: ID is unused\n";
				exit(1);
				return;
			}
			
			Object* deletedObject = (Object*)&data[GetOffset(idToIndex[instanceId])];
			Object* lastObject = (Object*)&data[GetOffset(count - 1)];

			memcpy(deletedObject, lastObject, elementSize);

			idToIndex[lastObject->instanceId] = idToIndex[instanceId];
			idToIndex.erase(instanceId);

			count--;
		}

		inline void* Get(InstanceId instanceId) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Get(id = " << instanceId << "):\n";
			if (MISSAN_DEBUG_ARRAY && !IsIdUsed(instanceId))std::cout << "\tID is unused\n";
			return IsIdUsed(instanceId) ? &data[GetOffset(idToIndex[instanceId])] : nullptr;
		}

	};

	template<class T>
	class ObjectArray : public ObjectArrayBase {

		inline void PrintTypeName() {
			if(MISSAN_DEBUG_ARRAY) std::cout << "<" << typeName << ">";
		}

	public:
		ObjectArray() : ObjectArrayBase(sizeof(T), typeid(T).name()) {}

		inline RawArray<T> AsRawArray() const {
			return RawArray<T>(data, count);
		}

		inline void Add(InstanceId instanceId, T* originalObject = nullptr) {
			PrintTypeName();
			T tempObj;
			ObjectArrayBase::Add(instanceId, originalObject ? &tempObj : originalObject);
		}

		inline T* Get(InstanceId instanceId) {
			PrintTypeName();
			return (T*)ObjectArrayBase::Get(instanceId);
		}

		inline void Remove(InstanceId instanceId) {
			PrintTypeName();
			ObjectArrayBase::Remove(instanceId);
		}

	};

}