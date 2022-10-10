#pragma once

#include "graphics/color.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "inspectable.hpp"
#include "ecs/object.hpp"

namespace Missan {

	class Material : public Object {

	public:
		glm::vec4 ambient = Color::white;
		glm::vec4 diffuse = Color::white;
		glm::vec4 specular = Color::white;
		float shininess = 32.0f;

		Shader* shader = nullptr;
		Texture* texture = nullptr;

		void DisplayInInspector();
		
	};

}