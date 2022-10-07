#pragma once

#include <stdlib.h>

// convenient wrapper for array
// without using any std containers which do unnecessary copying
template<class T>
class RawArray {
public:
	T* data;
	size_t count;

	RawArray(void* data, size_t count, bool makeCopy = false) {
		this->count = count;
		this->data = makeCopy ? (T*)memcpy(this->data, data, sizeof(T) * count) : (T*)data;
	}

	inline T& operator[](size_t index) {
		return data[index];
	}
};