#pragma once

#include <string>

#include "graphics/mesh.hpp"
#include "graphics/texture.hpp"

namespace missan {

    namespace Resources {

        Mesh*    GetMesh   (const std::string& fileName);
        Texture* GetTexture(const std::string& fileName);

        // not part of public API
        void Initialize();
        void Terminate();

    }

}