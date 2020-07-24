#pragma once

//#include "window.hpp"
//#include "camera.hpp"
//#include "components/transform.hpp"
//#include "gameobject.hpp"

namespace missan {

	namespace GUI {
		
		void Initialize();
		void Run();
		void Terminate();

		// submit function to be called in GUI::Run()
		void Submit(void (*func)());
		
	}

}
