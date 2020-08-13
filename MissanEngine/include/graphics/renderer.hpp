#pragma once

#include "missanpch.hpp"
#include "core/component.hpp"
#include "graphics/texture.hpp"
#include "graphics/mesh.hpp"

namespace Missan {

    /// 
/// Renders GameObject with Mesh and Texture using its Transform
    class Renderer : public Component{

    public:

        /// 
/// Mesh to render
        Mesh* mesh_ptr = nullptr;

        /// 
/// Texture to render
        Texture* texture_ptr = nullptr;



        /// 
/// NOT PART OF PUBLIC API //////////////////////////////////////////
        Renderer* Clone() const { return new Renderer(*this); }   
        void OnRender();

    };

}