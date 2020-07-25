#pragma once

#include "missanpch.hpp"
#include "components/component.hpp"
#include "graphics/mesh.hpp"
#include "core/resources.hpp"


namespace missan {

	class Collider : public Component {

	public:

		// Mesh to use as collider. simple shapes recommended
		Mesh* mesh_ptr = nullptr;



		bool OverlapsWith(Collider& other);

		bool OverlapOnAxis(
			std::vector<glm::vec3>& va, 
			std::vector<glm::vec3>& vb, 
			glm::vec3& axis);

		std::pair<float, float> CalcProjMinMax(
			std::vector<glm::vec3>& points,
			glm::vec3& normal);

		void Start() {
			mesh_ptr = Resources::GetMesh("unitCube");
		}

		void OnPhysicsUpdate() {

			/*
void CheckCollisions(Scene& scene) {
	for (auto* a : scene.gameObjects) {
		Collider& ca = a->GetCollider();

		for (auto* b : scene.gameObjects) {
			if (a == b) continue;
			Collider& cb = b->GetCollider();

			if (ca.OverlapsWith(cb)) {
				// collision happened, do something
				std::cout << "collision detected\n";
			}

		}
	}
}
*/
		}



		// NOT PART OF PUBLIC API ////////////////////////
		Collider* Clone() const { return new Collider(*this); }

	};

}