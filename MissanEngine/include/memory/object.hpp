#pragma once

#include "inspectable.hpp"

#include <string>

namespace Missan {

	///
	/// All objects that can be referenced by Missan. 
	class Object : public Inspectable {

	public:

		// TODO: mv to separate arr?
		// todo: some func for making each name unique?
		std::string name = "sdfhsdfkjsdhgfkjdshg";

		typedef size_t IdType;

		IdType id = NULL;

		static IdType GetUniqueId();

	};

}