#pragma once

#include "ecs.hpp"
#include "transform.hpp"
#include "color.hpp"
#include "renderer.hpp"

#include <vector>

namespace Missan {

	// axis aligned bounding box. used for 1st sweep to find potential overlaps. 
	class Aabb {

	public:

		glm::vec3 min = { -.5, -.5, -.5 };
		glm::vec3 max = { .5, .5, .5 };
		glm::vec3 size = { 1, 1, 1 };
		glm::vec3 extents = { .5, .5, .5 };


	};


	/// 
	/// Class that detects collisions against other Colliders. 
	/// Colliders are affected by the scale and rotation of the Transform. 
	class Collider : public Component<Collider> {

	public:

		///
		/// The shapes that the Collider class supports. 
		enum class Shape { 
			
			///
			/// A cuboid
			Box,
			
			///
			/// A sphere. The sphere Collider will be scaled by the largest component of
			/// the Transform's scale, so that it always encapsulates the object. 
			Sphere 
		};

		///
		/// The shape of this collider. 
		Shape shape = Shape::Box;

		///
		/// The offset (in local space) of this Collider relative to the Transform's origin. 
		glm::vec3 center = { 0, 0, 0 };	// todo: make relevant

		///
		/// The size of this Collider in along the x,y,z axes. Size is modifed by the
		/// scale of the Transform. Sphere Colliders do not use size. 
		glm::vec3 size = { 1, 1, 1 };

		///
		/// The radius of the sphere Collider. Box Colliders do not use radius. 
		float& radius = size[0];

		//for future capsule Colliders:
		// float& height = size[1];
		// int& direction = size[2];
		// alternatively, use union

		Aabb aabb;
		bool isColliding = false;

		void Start() {
			if (shape == Shape::Sphere) radius = 0.5f;
		}

		void OnCollisionStay(Collision collision) {
			isColliding = true;
			GetComponent<Renderer>()->material->ambient = Color::red;
		}

		void OnCollisionExit(Collision collision) {
			isColliding = false;
			GetComponent<Renderer>()->material->ambient = Color::green;
		}

		void DisplayInInspector() {

			using namespace ImGui;
			if (shape == Shape::Box) {
				if (CollapsingHeader("Box Collider")) {
					DragFloat3("size", (float*)&size, 0.01f);
					Checkbox("Is Colliding?", &isColliding);
				}
			}
			else if (shape == Shape::Sphere) {
				if (CollapsingHeader("Sphere Collider")) {
					DragFloat("radius", &radius, 0.01f);
					Checkbox("Is Colliding?", &isColliding);
				}
			}
		}

	};

}