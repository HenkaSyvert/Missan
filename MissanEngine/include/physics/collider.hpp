#pragma once

#include "component.hpp"
#include "transform.hpp"
#include "graphics/color.hpp"
#include "graphics/renderer.hpp"

#include <vector>

namespace Missan {

	// axis aligned bounding box. used for 1st sweep to find potential overlaps. 
	class Aabb {

	public:

		// todo: these are inter dependent, make properties?
		glm::vec3 min = { -.5, -.5, -.5 };
		glm::vec3 max = { .5, .5, .5 };
		glm::vec3 size = { 1, 1, 1 };
		glm::vec3 extents = { .5, .5, .5 };


	};


	/// 
	/// Class that detects collisions against other Colliders
	class Collider : public Component<Collider> {

	public:

		enum class Shape { box, sphere };
		Shape shape = Shape::box;

		glm::vec3 center = { 0, 0, 0 };	// todo: make relevant
		glm::vec3 size = { 1, 1, 1 };
		float& radius = size[0];
		//for future capsules:
		// float& height = size[1];
		// int& direction = size[2];
		// alternatively, use union

		Aabb aabb;
		bool isColliding = false;

		void Start() {
			if (shape == Shape::sphere) radius = 0.5f;
		}

		void OnCollisionStay(GameObject* other) {
			isColliding = true;
			GetComponent<Renderer>()->material->ambient = Color::red;
		}

		void OnCollisionExit(GameObject* other) {
			isColliding = false;
			GetComponent<Renderer>()->material->ambient = Color::green;
		}

		void DisplayInInspector() {

			using namespace ImGui;
			if (shape == Shape::box) {
				if (CollapsingHeader("Box Collider")) {
					DragFloat3("size", (float*)&size, 0.01f);
					Checkbox("Is Colliding?", &isColliding);
				}
			}
			else if (shape == Shape::sphere) {
				if (CollapsingHeader("Sphere Collider")) {
					DragFloat("radius", &radius, 0.01f);
					Checkbox("Is Colliding?", &isColliding);
				}
			}
		}

	};

}