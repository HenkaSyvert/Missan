#pragma once

#include "component.hpp"
#include "transform.hpp"

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

		Transform* transform;

		float OverlapsWith(Collider* other);

		glm::vec3 center = { 0, 0, 0 };
		Aabb aabb;



		bool isColliding = false;

		void Start();
		virtual void OnCollisionEnter(GameObject* other);
		virtual void OnCollisionStay(GameObject* other);
		virtual void OnCollisionExit(GameObject* other);

	};

	class BoxCollider : public Collider {

	public:
		glm::vec3 size = { 1, 1, 1 };

		void DisplayInInspector() {

			using namespace ImGui;
			if (CollapsingHeader("Box Collider")) {
				DragFloat3("size", (float*)&size, 0.01f);
				Checkbox("Is Colliding?", &isColliding);
			}

		}

	};

	class SphereCollider : public Collider {

	public:
		// todo: change to radius = 0.5, unity does it that way. 
		float radius = 1;

		void DisplayInInspector() {

			using namespace ImGui;
			if (CollapsingHeader("Sphere Collider")) {
				DragFloat("radius", &radius, 0.01f);
				Checkbox("Is Colliding?", &isColliding);
			}

		}

	};

}