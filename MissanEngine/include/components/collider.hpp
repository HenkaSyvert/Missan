#pragma once

#include "missanpch.hpp"
#include "components/component.hpp"
#include "graphics/mesh.hpp"


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

		void OnPhysicsUpdate() {

			std::vector<float> translatedVertices = mesh_ptr->vertices;
			for (int i = 0; i < translatedVertices.size(); i += 3) {

			}

		}



		// NOT PART OF PUBLIC API ////////////////////////
		Collider* Clone() const { return new Collider(*this); }

	};

}