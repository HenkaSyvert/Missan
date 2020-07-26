#include "components/collider.hpp"

#include "components/transform.hpp"

using namespace missan;

// PUBLIC



bool Collider::OverlapsWith(Collider* other) {

	// using separated axis theorem (SAT)
	// normals that needs to be tested:
	// face normals for A
	// + face normals for B
	// + face normals of all pairs of edges from A and B

	auto va = mesh_ptr->GetVerticesVec3();
	auto vb = other->mesh_ptr->GetVerticesVec3();

	// TODO, add normals from edge pairs...

	for (auto& n : mesh_ptr->GetNormals()) 
		if (!OverlapOnAxis(va, vb, n)) 
			return false;
		
	
	for (auto& n : other->mesh_ptr->GetNormals())
		if (!OverlapOnAxis(va, vb, n)) return false;

	std::cout << "there was collision\n";

	return true;
}



bool Collider::OverlapOnAxis(
	std::vector<glm::vec3>& va,
	std::vector<glm::vec3>& vb,
	glm::vec3& axis)
{
	std::pair<float, float> shadowA = CalcProjMinMax(va, axis);
	std::pair<float, float> shadowB = CalcProjMinMax(vb, axis);

	return shadowA.first < shadowB.second
		&& shadowA.second > shadowB.first;
}

std::pair<float, float> Collider::CalcProjMinMax(
	std::vector<glm::vec3>& points, 
	glm::vec3& normal) 
{
	float min = INFINITY;
	float max = -INFINITY;

	for (auto& p : points) {
		float a = glm::dot(p, normal);
		if (a < min) min = a;
		if (a > max) max = a;
	}

	return { min, max };

}
