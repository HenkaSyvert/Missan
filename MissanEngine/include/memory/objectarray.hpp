#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <typeinfo>

#include "rawarray.hpp"
#include "object.hpp"

// TODO: make actual dynamic size work, but now i am lazy
#define MAX_GAME_OBJECTS 200

#define MISSAN_DEBUG_ARRAY 0

namespace Missan {


	///
	/// Dynamic, contiguous, associative array
	class ObjectArrayBase {
	protected:
		char* data = nullptr;
		std::unordered_map<size_t, size_t> idToIndex;
		std::unordered_map<size_t, size_t> indexToId;
		size_t count = 0;
		const size_t elementSize;
		size_t capacity = MAX_GAME_OBJECTS;


		inline bool IsIdUsed(Object::IdType id) const {
			return idToIndex.find(id) != idToIndex.end();
		}

		inline size_t GetOffset(Object::IdType index) const {
			return index * elementSize;
		}

	public:

		const std::string typeName;

		ObjectArrayBase(size_t elementSize, const char* name)
			: elementSize(elementSize),
			typeName(name)
		{
			data = (char*)malloc(GetOffset(capacity));
		}

		inline RawArrayBase AsRawArrayBase() const {
			return RawArrayBase(data, count, elementSize);
		}

		void Add(Object::IdType id, const void* const element) {
			if (MISSAN_DEBUG_ARRAY) std::cout
				<< "Add(id = " << id
				<< ", element = " << element << "):\n";

			// if try to add ID == NULL, just ignore
			if (!id) {
				if (MISSAN_DEBUG_ARRAY) std::cout << "\terr: ID is NULL\n";
				exit(1);
				return;
			}

			if (IsIdUsed(id)) {
				// no support for game object to have multiple components of same type, just ignore. 
				if(MISSAN_DEBUG_ARRAY)std::cout << "\terr: ID is not used\n";
				exit(1);
				return;
			}

			size_t index = count++;
			if (count > capacity) {
				capacity *= 2;
				data = (char*)realloc(data, GetOffset(capacity));
			}

			indexToId[index] = id;
			idToIndex[id] = index;

			memcpy(&data[GetOffset(index)], element, elementSize);
		}

		void Remove(Object::IdType id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Remove(id = " << id << "):\n";

			if (!IsIdUsed(id)) {
				// intentionally quietly ignore try to remove non existant component, means dont need check prior. 
				if (MISSAN_DEBUG_ARRAY)std::cout << "\terr: ID is unused\n";
				exit(1);
				return;
			}

			size_t indexOfRemoved = idToIndex[id];
			size_t indexOflast = count - 1;
			Object::IdType idOfLast = indexToId[indexOflast];

			char* removedElement = &data[GetOffset(indexOfRemoved)];
			char* lastElement = &data[GetOffset(indexOflast)];
			memcpy(removedElement, lastElement, elementSize);

			idToIndex[idOfLast] = indexOfRemoved;
			indexToId[indexOfRemoved] = idOfLast;
			indexToId.erase(indexOflast);
			idToIndex.erase(id);

			count--;
		}

		// for getting specific element by index
		inline void* Get(Object::IdType id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "Get(id = " << id << "):\n";
			if (MISSAN_DEBUG_ARRAY && !IsIdUsed(id))std::cout << "\tID is unused\n";
			return IsIdUsed(id) ? &data[GetOffset(idToIndex[id])] : nullptr;
		}

		inline void* Get(const std::string& name) {
			for (int i = 0; i < count; i++)
				if (!((Object*)data[i])->name.compare(name))
					return &data[i];
			return nullptr;
		}

	};

	template<class T>
	class ObjectArray : public ObjectArrayBase {
	public:
		ObjectArray()
			: ObjectArrayBase(sizeof(T), typeid(T).name()) {}

		inline RawArray<T> AsRawArray() const {
			return RawArray<T>(data, count);
		}

		inline void Add(Object::IdType id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "<" << typeid(T).name() << ">";
			T component;
			ObjectArrayBase::Add(id, &component);
		}

		inline T* Get(Object::IdType id) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "<" << typeid(T).name() << ">";
			return (T*)ObjectArrayBase::Get(id);
		}

		inline T* Get(const std::string& name) {
			if (MISSAN_DEBUG_ARRAY)std::cout << "<" << typeid(T).name() << ">";
			return (T*)ObjectArrayBase::Get(name);
		}

	};

}