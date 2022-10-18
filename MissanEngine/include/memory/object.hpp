#pragma once

#include "inspectable.hpp"
#include "idtypes.hpp"

#include <string>

namespace Missan {

	class ObjectArrayBase;

	///
	/// All objects that can be referenced by Missan. 
	class Object : public Inspectable {

	public:

		InstanceId instanceId = NULL;

		std::string name = "Object";

	};

}