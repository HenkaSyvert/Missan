#pragma once

#include "inspectable.hpp"
#include "idtypes.hpp"

#include <string>

namespace Missan {

	class ObjectArrayBase;

	///
	/// All objects that can be referenced by Missan. 
	class Object : public Inspectable {

		InstanceId _instanceId = NULL;

		friend ObjectArrayBase;

	public:

		// TODO: mv to separate arr?
		// todo: some func for making each name unique?
		std::string name = "sdfhsdfkjsdhgfkjdshg";

		const InstanceId& instanceId = _instanceId;

	};

}