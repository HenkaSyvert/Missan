#pragma once

#include "ecs/gameobject.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"

namespace Missan {

	/// 
	/// The core module
	namespace Engine {

		/// 
		/// Initializes the engine. Must be called before ALL other Missan functions. 
		void Initialize();

		/// 
		/// Runs the engine. Setup up your Scene prior to calling Run().
		void Run();

		void Quit();

	}

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

	//// 
	/// Functions for accessing assets used by the game
	namespace Resources {


		// TODO: move these 2 into Texture and Mesh respectively, 
		// and manage them in contiguous arrays.. 
		
		//// 
		/// Returns pointer to Mesh, loads if necessary
		Mesh* GetMesh(const std::string& fileName);

		//// 
		/// Returns pointer to Texture, loads if necessary
		Texture* GetTexture(const std::string& fileName);

	}

}

