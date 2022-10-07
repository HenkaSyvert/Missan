#pragma once

#include <unordered_map>
#include <iostream>

#include "util/rawarray.hpp"

class PackedAssociativeArrayBase {
protected:
	char* data = nullptr;
	std::unordered_map<size_t, size_t> idToIndex;
	std::unordered_map<size_t, size_t> indexToId;

	size_t count = 0;
	size_t capacity = 2;

	inline bool IsIdUsed(size_t id) {
		return idToIndex.find(id) != idToIndex.end();
	}

	inline size_t GetOffset(size_t index) {
		return index * elementSize;
	}

public:
	size_t elementSize;

	PackedAssociativeArrayBase(size_t elementSize) {
		
		this->elementSize = elementSize;
		data = (char*)malloc(GetOffset(capacity));
		//std::cout << "packed arr init w el size: " << elementSize << "\nand alloacted " << GetOffset(capacity) << " bytes\n";
	}

	inline RawArrayBase AsRawArrayBase() const {
		return RawArrayBase(data, count, elementSize);
	}



	void Add(size_t id, void* element) {

		//if (IsIdUsed(id)) std::cout << "id: " << id << " is already associated with index, cant add element\n";
		
		size_t index = count++;
		if (count > capacity) {
			std::cout << "needs resize\n";
			capacity *= 2;
			data = (char*)realloc(data, GetOffset(capacity));
		}

		indexToId[index] = id;
		idToIndex[id] = index;

		memcpy(&data[GetOffset(index)], element, elementSize);
	}

	void Remove(size_t id) {

		if (!IsIdUsed(id)) {
			//std::cout << "id: " << id << " is not associated with index, can't remove element\n";
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

		if (!IsIdUsed(id)) {
			//std::cout << "id: " << id << " is not associated with any index, can't get\n";
			return nullptr;
		}

		size_t index = idToIndex[id];
		return &data[GetOffset(index)];

	}

};


template<class T>
class PackedAssociativeArray : public PackedAssociativeArrayBase {

public:
	PackedAssociativeArray() : PackedAssociativeArrayBase(sizeof(T)){}

	inline RawArray<T> AsRawArray() const {
		return RawArray<T>(data, count);
	}

	void Add(size_t id) {
		T component;
		PackedAssociativeArrayBase::Add(id, &component);
	}

	T* Get(size_t id) {
		return (T*)PackedAssociativeArrayBase::Get(id);
	}

};