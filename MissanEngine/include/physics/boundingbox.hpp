#pragma once

#include <vector>

#include <glm/vec3.hpp>

namespace Missan {

	/// 
	/// Class that represents a 3D bounding box
	class BoundingBox {

	public:

		/// 
		/// The size of this bounding box
		glm::vec3 size = { 1,1,1 };

		/// 
		/// The vertices of this bounding box
		std::vector<glm::vec3> GetVertices();

		/// 
		/// The face normals of this bounding box
		std::vector<glm::vec3> GetNormals();

		/// 
		/// Vectors representing the edges (vertex-i - vertex-j)
		std::vector<glm::vec3> GetEdgeVectors();
		
	};

}