#pragma once

#include "missanpch.hpp"
#include "graphics/mesh.hpp"
#include "graphics/texture.hpp"

namespace Missan {

    // Functions for accessing assets used by the game
    namespace Resources {

        // Put your Textures here. it's also ok to make subfolders in there
        // but you still must provide the relative full filename then
        extern std::string textureDirectory;

        // Put your Meshes here. it's also ok to make subfolders in there
        // but you still must provide the relative full filename then
        extern std::string meshDirectory;



        // Returns pointer to Mesh, loads if necessary, from the Mesh directory
        Mesh* GetMesh(const std::string& fileName);

        // Returns pointer to Texture, loads if necessary, from the Texture directory
        Texture* GetTexture(const std::string& fileName);



        // NOT PART OF PUBLIC API /////////////////////////////
        void Initialize();
        void Terminate();

    }

}
