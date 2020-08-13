#pragma once

/// 
/// MissanEngine public API


/// 
/// temporary, for access to GLFW_KEYCODE
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/// 
/// temporary, mathematics library
#include <glm/glm.hpp>

/// 
/// temporary, gui library
#include <imgui/imgui.h>

/// 
/// temporary, as logging to console
#include <iostream>

/// 
/// Missan includes
#include "core/component.hpp"
#include "core/engine.hpp"
#include "core/gameobject.hpp"
#include "core/gui.hpp"
#include "core/input.hpp"
#include "core/resources.hpp"
#include "core/scene.hpp"
#include "core/time.hpp"
#include "core/transform.hpp"
#include "core/window.hpp"

#include "graphics/camera.hpp"
#include "graphics/graphics.hpp"
#include "graphics/mesh.hpp"
#include "graphics/renderer.hpp"
#include "graphics/shaderprogram.hpp"
#include "graphics/texture.hpp"

#include "physics/collider.hpp"
#include "physics/physics.hpp"
#include "physics/rigidbody.hpp"

