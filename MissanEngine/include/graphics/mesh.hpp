#pragma once

namespace Missan {

	/// 
	/// Stores data about 3D model
	class Mesh {

	public:
		int vaoId;

		// vertices.size() * 3
		int elementCount;

		/// 
		/// Creates new Mesh
		Mesh(int vaoId, int elementCount) {
			this->vaoId = vaoId;
			this->elementCount = elementCount;
		}


	};

}