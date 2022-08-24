#pragma once

#include "component.hpp"
#include "texture.hpp"
#include "mesh.hpp"

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



        Renderer* Clone() const { return new Renderer(*this); }   
        void OnRender();

    };

}