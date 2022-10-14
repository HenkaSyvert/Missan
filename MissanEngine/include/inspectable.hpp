#pragma once

#include <imgui/imgui.h>

namespace Missan {

	// TODO: make objs inspectable some other way, to reduce coupling, 
	// should be a separate editor thing, not concern for engine. 
	// unless use #ifdef MISSAN_EDITOR?
	class Inspectable {
	public:
		inline virtual void DisplayInInspector() {}

	};

}