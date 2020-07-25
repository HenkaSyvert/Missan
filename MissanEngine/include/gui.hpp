#pragma once

//#include "window.hpp"
//#include "camera.hpp"
//#include "components/transform.hpp"
//#include "gameobject.hpp"

namespace missan {

	namespace GUI {
		

		// none of this should probably be public
		void Initialize();
		void Begin();		// called by Engine BEFORE all user-made calls
		void End();			// called by Engine AFTER all user-made calls
		void Terminate();

		
	}

}
