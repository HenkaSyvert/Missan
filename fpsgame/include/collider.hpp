#pragma once

#include <glm/glm.hpp>

#include "transform.hpp"
#include "mesh.hpp"

#include <vector>

namespace missan {

	class Collider {

	private:
		Transform* transform_ptr = nullptr;
		Mesh* mesh_ptr = nullptr;
		bool isEnabled = false;

	public:

		std::vector<glm::vec3> GetTranslatedVertices();
		void Enable(bool enable = true);
		void SetMesh(Mesh& mesh);
		Mesh& GetMesh();
		bool OverlapsWith(Collider& other);
		bool IsEnabled();

		Transform& GetTransform();
		void SetTransform(Transform& transform);

		bool OverlapOnAxis(
			std::vector<glm::vec3>& va, 
			std::vector<glm::vec3>& vb, 
			glm::vec3& axis);
		std::pair<float, float> CalcProjMinMax(
			std::vector<glm::vec3>& points,
			glm::vec3& normal);
		std::vector<glm::vec3> CalcNormals(
			std::vector<glm::vec3>& vertices,
			std::vector<unsigned int>& indices);

	};

}