#pragma once

namespace Missan {

	namespace GUI {
		

		// NOT PART OF PUBLIC API //////////////////////////////////
		void Initialize();

		// called by Engine BEFORE all user-made calls
		void Begin();		

		// called by Engine AFTER all user-made calls
		void End();			

		void Terminate();

		
	}

}
