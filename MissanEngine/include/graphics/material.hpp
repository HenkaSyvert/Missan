#pragma once

#include "graphics/color.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "inspectable.hpp"
#include "ecs/object.hpp"

#include <string>

namespace Missan {

	class Material : public Object {

	public:
		glm::vec4 ambient = Color::white;
		glm::vec4 diffuse = Color::white;
		glm::vec4 specular = Color::white;
		float shininess = 32.0f;

		IdType shaderId = NULL;
		IdType textureId = NULL;

		void DisplayInInspector();
		
		static void Load(const std::string& name);

	};

}