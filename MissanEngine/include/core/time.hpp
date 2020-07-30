#pragma once

namespace Missan {
	
	// Interface to Time system
	namespace Time {

		// Time (in seconds) at the beginning of this frame, measured from start of game, modified by timeScale
		extern const float& time;

		// Time (in seconds) at the beginning of this frame, measured from start of game, not modified by timeScale
		extern const float& unscaledTime;
		
		// Time (in seconds) since last frame, modified by timeScale
		extern const float& deltaTime;

		// Time (in seconds) since last frame, not modified by timeScale
		extern const float& unscaledDeltaTime;

		// The scale at which time passes
		extern float timeScale;



		// NOT PART OF PUBLIC API ///////////////////
		void Update();

	}

}