#pragma once

#include <string>

namespace Missan {

	class Object {

	public:

		// TODO: mv to separate arr?
		// todo: some func for making each name unique?
		std::string name;

		typedef size_t IdType;

		IdType id;

		static IdType GetUniqueId();

	};

}