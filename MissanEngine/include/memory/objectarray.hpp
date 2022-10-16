#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <typeinfo>

#include "rawarray.hpp"
#include "object.hpp"

#define MISSAN_DEBUG_ARRAY 0

namespace Missan {

	typedef size_t InstanceId;

	///
	/// Dynamic, contiguous, associative array
	class ObjectArrayBase {
	protected:
		char* data = nullptr;
		std::unordered_map<InstanceId, size_t> idToIndex;
		size_t count = 0;
		const size_t elementSize;
		size_t capacity = 200;


		inline bool IsIdUsed(InstanceId id) const {
			return idToIndex.find(id) != idToIndex.end();
		}

		inline size_t GetOffset(InstanceId index) const {
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

		void Add(InstanceId id, const void* const original) {

			size_t index = count++;
			if (count > capacity) {
				capacity *= 2;
				data = (char*)realloc(data, GetOffset(capacity));
			}

			idToIndex[id] = index;
			
			Object* object = (Object*)&data[GetOffset(index)];
			memcpy(object, original, elementSize);
			object->id = id;
		}

		void Remove(InstanceId id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Remove(id = " << id << "):\n";

			if (!IsIdUsed(id)) {
				// intentionally quietly ignore try to remove non existant component, means dont need check prior. 
				if (MISSAN_DEBUG_ARRAY)std::cout << "\terr: ID is unused\n";
				exit(1);
				return;
			}
			
			Object* deletedObject = (Object*)&data[GetOffset(idToIndex[id])];
			Object* lastObject = (Object*)&data[GetOffset(count - 1)];

			memcpy(deletedObject, lastObject, elementSize);

			idToIndex[lastObject->id] = idToIndex[id];
			idToIndex.erase(id);

			count--;
		}

		inline void* Get(InstanceId id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Get(id = " << id << "):\n";
			if (MISSAN_DEBUG_ARRAY && !IsIdUsed(id))std::cout << "\tID is unused\n";
			return IsIdUsed(id) ? &data[GetOffset(idToIndex[id])] : nullptr;
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

		inline void Add(InstanceId id, T* object = nullptr) {
			PrintTypeName();
			T tempObj;
			ObjectArrayBase::Add(id, object ? &tempObj : object);
		}

		inline T* Get(InstanceId id) {
			PrintTypeName();
			return (T*)ObjectArrayBase::Get(id);
		}

		inline void Remove(InstanceId id) {
			PrintTypeName();
			ObjectArrayBase::Remove(id);
		}

	};

}