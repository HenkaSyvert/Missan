#pragma once

namespace Missan {

	/// 
	/// Stores data about 3D model. 
	class Mesh {

	public:

		///
		/// The vertex array object ID used by OpenGL to identify this Mesh. 
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