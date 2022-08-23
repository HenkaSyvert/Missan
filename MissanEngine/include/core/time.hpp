#pragma once

namespace Missan {
	
	/// 
	/// Interface to Time system
	namespace Time {

		/// 
		/// Time (in seconds) at the beginning of this frame, measured from start of game
		extern const float& time;
		
		/// 
		/// Time (in seconds) since last frame
		extern const float& deltaTime;

	}

}