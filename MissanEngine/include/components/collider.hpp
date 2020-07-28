#pragma once

#include "missanpch.hpp"
#include "components/component.hpp"
#include "graphics/mesh.hpp"
#include "core/resources.hpp"


namespace missan {

	class Collider : public Component {

	public:

		// Mesh to use as collider. simple shapes recommended
		Mesh* mesh_ptr = Resources::GetMesh("unitCube");



		bool OverlapsWith(Collider* other);

		bool OverlapOnAxis(
			std::vector<glm::vec3>& va, 
			std::vector<glm::vec3>& vb, 
			glm::vec3& axis);





		// NOT PART OF PUBLIC API ////////////////////////
		Collider* Clone() const { return new Collider(*this); }

	};

}