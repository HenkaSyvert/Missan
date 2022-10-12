#pragma once

#include <unordered_map>
#include <iostream>
#include <string>
#include <typeinfo>

#include "rawarray.hpp"
#include "object.hpp"

namespace Missan {

	class PackedAssociativeArrayBase {
	protected:
		char* data = nullptr;
		std::unordered_map<size_t, size_t> idToIndex;
		std::unordered_map<size_t, size_t> indexToId;
		size_t count = 0;
		const size_t elementSize;
		size_t capacity = 100;


		inline bool IsIdUsed(size_t id) const {
			return idToIndex.find(id) != idToIndex.end();
		}

		inline size_t GetOffset(size_t index) const {
			return index * elementSize;
		}

	public:

		const std::string typeName;

		PackedAssociativeArrayBase(size_t elementSize, const char* name)
			: elementSize(elementSize),
			typeName(name)
		{
			data = (char*)malloc(GetOffset(capacity));
		}

		inline RawArrayBase AsRawArrayBase() const {
			return RawArrayBase(data, count, elementSize);
		}

		void Add(size_t id, const void* const element) {
			if (IsIdUsed(id)) {
				// no support for game object to have multiple components of same type, just ignore. 
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

		void Remove(size_t id) {
			if (!IsIdUsed(id)) {
				// intentionally quietly ignore try to remove non existant component, means dont need check prior. 
				return;
			}

			size_t indexOfRemoved = idToIndex[id];
			size_t indexOflast = count - 1;
			size_t idOfLast = indexToId[indexOflast];

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
		inline void* Get(size_t id) {
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
	class PackedAssociativeArray : public PackedAssociativeArrayBase {
	public:
		PackedAssociativeArray()
			: PackedAssociativeArrayBase(sizeof(T), typeid(T).name()) {}

		inline RawArray<T> AsRawArray() const {
			return RawArray<T>(data, count);
		}

		inline void Add(size_t id) {
			T component;
			PackedAssociativeArrayBase::Add(id, &component);
		}

		inline T* Get(size_t id) {
			return (T*)PackedAssociativeArrayBase::Get(id);
		}

		inline T* Get(const std::string& name) {
			return (T*)PackedAssociativeArrayBase::Get(name);
		}

	};

}