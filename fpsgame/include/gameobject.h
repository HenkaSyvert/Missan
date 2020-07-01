#pragma once

#include <glm/glm.hpp>

#include "transform.h"
#include "model.h"

namespace missan {

	class GameObject {

	private:
		Transform transform;
		Model* model_ptr;

	public:
		GameObject(
			Model& model, 
			glm::vec3 pos = glm::vec3(0,0,0),
			glm::vec3 rot = glm::vec3(0,0,0)
		);

		Transform& GetTransform();
		Model& GetModel();

	};

}