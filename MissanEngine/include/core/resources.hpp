#pragma once

#include "missanpch.hpp"
#include "graphics/mesh.hpp"
#include "graphics/texture.hpp"

namespace missan {

    // Handles assets used by the game, i.e. 3D models, textures
    namespace Resources {

        // Returns pointer to Mesh, loads if necessary
        Mesh*    GetMesh   (const std::string& fileName);

        // Returns pointer to Texture, loads if necessary
        Texture* GetTexture(const std::string& fileName);



        // NOT PART OF PUBLIC API /////////////////////////////
        void Initialize();
        void Terminate();

    }

}