#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "gameobject.hpp"
#include "graphics/shaderprogram.hpp"
#include "components/camera.hpp"
#include "scene.hpp"
#include "components/component.hpp"
#include "graphics/texture.hpp"
#include "graphics/graphics.hpp"

#include "graphics/mesh.hpp"
#include "components/collider.hpp"

namespace missan {

    class Renderer : public Component{

    public:
        Mesh* mesh_ptr = nullptr;
        Texture* texture_ptr = nullptr;

        Renderer* Clone() const { return new Renderer(*this); }   // necessary for deep-cloning

        void OnRender();

    };

}