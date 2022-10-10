#pragma once

#include <stdlib.h>

// convenient wrapper for array
// without using any std containers which do unnecessary copying
// and both raw mem version and template

class RawArrayBase {
	char* const data = nullptr;
	const size_t elementSize;
	const bool isCopy = false;

	inline static char* InitData(const void* const newData, size_t count, size_t elementSize, bool makeCopy) {
		return count == 0 || elementSize == 0 ? nullptr
			: makeCopy ? (char*)memcpy(malloc(elementSize * count), newData, elementSize * count)
			: (char*)newData;
	}

public:
	const size_t count;

	RawArrayBase(const void* const newData, size_t count, size_t elementSize, bool makeCopy = false) :
		count(count),
		elementSize(elementSize),
		isCopy(makeCopy),
		data(InitData(newData, count, elementSize, makeCopy)) 
	{ }

	~RawArrayBase() {
		if (isCopy) free(data);
	}

	inline void* operator[](size_t index) const {
		return data + elementSize * index;
	}
};

template<class T>
class RawArray : public RawArrayBase{
public:
	RawArray(const void* const newData, size_t count, bool makeCopy = false) 
		: RawArrayBase(newData, count, sizeof(T), makeCopy) 
	{ }

	inline T& operator[](size_t index) const {
		return *(T*)RawArrayBase::operator[](index);
	}
};