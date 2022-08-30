#pragma once

#include "mesh.hpp"
#include "texture.hpp"
#include <string>


namespace Missan {

    //// 
    /// Functions for accessing assets used by the game
    namespace Resources {

        /// 
        /// Put your Textures here. it's also ok to make subfolders in there
        /// but you still must provide the relative full filename then
        extern std::string textureDirectory;


        //// 
        /// Returns pointer to Mesh, loads if necessary
        Mesh* GetMesh(const std::string& fileName);

        //// 
        /// Returns pointer to Texture, loads if necessary
        Texture* GetTexture(const std::string& fileName);

    }

}
