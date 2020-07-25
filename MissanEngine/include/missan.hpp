#pragma once

// MissanEngine public API


// temporary, for access to GLFW_KEYCODE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// temporary, mathematics library
#include <glm/glm.hpp>

// temporary, gui library
#include <imgui/imgui.h>

// temporary, as logging to console
#include <iostream>

// Missan includes
#include "components/camera.hpp"
#include "components/collider.hpp"
#include "components/component.hpp"
#include "components/renderer.hpp"
#include "components/transform.hpp"

#include "core/engine.hpp"
//#include "core/gui.hpp"		// currently uses imgui directly for gui API
#include "core/input.hpp"
#include "core/resources.hpp"
#include "core/window.hpp"
#include "core/time.hpp"

#include "graphics/mesh.hpp"
#include "graphics/graphics.hpp"
#include "graphics/shaderprogram.hpp"
#include "graphics/texture.hpp"

#include "gameobject.hpp"
#include "scene.hpp"



