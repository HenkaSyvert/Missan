#pragma once

#include <imgui/imgui.h>

namespace Missan {

	///
	/// Interface for objects that can be shown in the Inspector window. 
	class Inspectable {

	public:

		///
		/// Display this object in the Inspector. 
		inline virtual void DisplayInInspector() {}

	};

}