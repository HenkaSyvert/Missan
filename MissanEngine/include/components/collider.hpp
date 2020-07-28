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



		float OverlapsWith(Collider* other);





		// NOT PART OF PUBLIC API ////////////////////////
		Collider* Clone() const { return new Collider(*this); }

	};

}