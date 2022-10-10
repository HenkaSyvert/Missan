#pragma once

#include "ecs/object.hpp"

namespace Missan {

	/// 
	/// Stores data about 3D model
	class Mesh : public Object {

	public:
		int vaoId;

		// vertices.size() * 3
		int elementCount;

		/// 
		/// Creates new Mesh
		Mesh(int vaoId, int vertexCount);

	};

}