#pragma once

#include "component.hpp"
#include "transform.hpp"

#include <vector>

namespace Missan {

	/// 
	/// Class that detects collisions against other Colliders
	class Collider : public Component<Collider> {

	public:

		enum class Shape { box, sphere };

		Transform* transform;

		// this is probably very inefficient
		std::vector<Collider*> overlappingColliders;

		/// 
		/// The amount of overlap between this Collider and other. 0 means no overlap
		glm::vec3 OverlapsWith(Collider* other);

		glm::vec3 size = { 1,1,1 };

		inline std::vector<glm::vec3> GetVertices() {
			
			float x = size.x / 2;
			float y = size.y / 2;
			float z = size.z / 2;
			return {
				{  x, -y, -z },
				{  x, -y,  z },
				{  x,  y, -z },
				{  x,  y,  z },
				{ -x, -y, -z },
				{ -x, -y,  z },
				{ -x,  y, -z },
				{ -x,  y,  z }
			};

		}

		/// 
		/// The face normals of this bounding box
		inline std::vector<glm::vec3> GetNormals() {
			return {
				{ 1,0,0 },
				{ 0,1,0 },
				{ 0,0,1 }
			};
		}

		/// 
		/// Vectors representing the edges (vertex-i - vertex-j)
		inline std::vector<glm::vec3> GetEdgeVectors() {
			return {
				{ 1,0,0 },
				{ 0,1,0 },
				{ 0,0,1 }
			};
		}

		void DisplayInInspector() {

			using namespace ImGui;


		}


		void Start();

	};

}