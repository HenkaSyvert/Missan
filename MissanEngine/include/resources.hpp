#pragma once

#include "memory/object.hpp"

namespace Missan {

	namespace Resources {

		template<class T>
		inline T* Get(Object::IdType id) {
			return Memory::Get<T>(id);
		}

		template<class T>
		inline T* Get(std::string name) {
			RawArray<T> arr = Memory::AsRawArray<T>();
			for (size_t i = 0; i < arr.count; i++)
				if (name == arr[i].name) return &arr[i];
		}


		// TODO: move to resources
		template<class T>
		inline T* Get(const std::string& name) {
			return GetArray<T>().Get(name);
		}

	}

}