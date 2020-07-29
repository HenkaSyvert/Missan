#pragma once

#include "missanpch.hpp"

namespace missan {

	// Class that represents a 3D bounding box
	class BoundingBox {

	public:

		// The size of this bounding box
		glm::vec3 size = { 1,1,1 };

		// The vertices of this bounding box
		std::vector<glm::vec3> GetVertices() {
			std::vector<glm::vec3> v;
			auto x = size.x/2, y = size.y/2, z = size.z/2;
			v.push_back({ x, -y, -z});
			v.push_back({ x, -y,  z});
			v.push_back({ x,  y, -z});
			v.push_back({ x,  y,  z});
			v.push_back({-x, -y, -z});
			v.push_back({-x, -y,  z});
			v.push_back({-x,  y, -z});
			v.push_back({-x,  y,  z});
			return v;
		}

		// The face normals of this bounding box
		std::vector<glm::vec3> GetNormals() {
			std::vector<glm::vec3> v;
			v.push_back({ 1,0,0 });
			v.push_back({ 0,1,0 });
			v.push_back({ 0,0,1 });
			return v;
		}

		// Vectors representing the edges (vertex-i - vertex-j)
		std::vector<glm::vec3> GetEdgeVectors() {
			// Just happens to be the same
			return GetNormals();
		}

		// Extends this BoundingBox to encapsulate the points
		void EncapsulatePoints(std::vector<glm::vec3>& points) {
			float x = 0, y = 0, z = 0;
			for (auto& p : points) {
				x = std::max(abs(p.x), x);
				y = std::max(abs(p.y), y);
				z = std::max(abs(p.z), z);
			}
			size = { 2 * x, 2 * y, 2 * z };
		}
		



	};

}