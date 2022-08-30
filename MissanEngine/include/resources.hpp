#pragma once

#include "mesh.hpp"
#include "texture.hpp"
#include <string>


namespace Missan {

    //// 
    /// Functions for accessing assets used by the game
    namespace Resources {

        //// 
        /// Returns pointer to Mesh, loads if necessary
        Mesh* GetMesh(const std::string& fileName);

        //// 
        /// Returns pointer to Texture, loads if necessary
        Texture* GetTexture(const std::string& fileName);

    }

}
