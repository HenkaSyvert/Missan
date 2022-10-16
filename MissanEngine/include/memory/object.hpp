#pragma once

#include "inspectable.hpp"

#include <string>

namespace Missan {

	typedef size_t InstanceId;

	///
	/// All objects that can be referenced by Missan. 
	class Object : public Inspectable {

	public:

		// TODO: mv to separate arr?
		// todo: some func for making each name unique?
		std::string name = "sdfhsdfkjsdhgfkjdshg";

		InstanceId id = NULL;

	};

}