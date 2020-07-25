#pragma once

namespace missan {
	
	// Interface to Time system
	namespace Time {

		// Time (in seconds) at the beginning of this frame, measured from start of game
		extern const double& time;

		// Time (in seconds) since last frame 
		extern const double& deltaTime;



		// NOT PART OF PUBLIC API ///////////////////
		void Update();

	}

}