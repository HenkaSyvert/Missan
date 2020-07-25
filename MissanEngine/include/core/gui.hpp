#pragma once

namespace missan {

	namespace GUI {
		

		// NOT PART OF PUBLIC API //////////////////////////////////
		void Initialize();
		void Begin();		// called by Engine BEFORE all user-made calls
		void End();			// called by Engine AFTER all user-made calls
		void Terminate();

		
	}

}
