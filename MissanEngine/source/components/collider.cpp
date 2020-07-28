#include "components/collider.hpp"

#include "components/transform.hpp"

#include <algorithm>	// std::min, std::max

using namespace missan;

// PUBLIC



bool Collider::OverlapsWith(Collider* other) {

	// The Separating axis Theorem: 2 sets of points, forming convex bodies, 
	// DO NOT overlap IF you can find a separating plane between them. 
	// which is done by projecting the points from both sets onto the normals
	// of all possible separating planes and check if their shadows overlap.
	
	std::vector<glm::vec3> normalsToCheck;

	auto ourTransform = GetGameObject().GetComponent<Transform>();
	auto theirTransform = other->GetGameObject().GetComponent<Transform>();

	// first we need our own transformed face-normals
	for (auto& n : ourTransform->TransformPoints(mesh_ptr->GetNormals()))
		normalsToCheck.push_back(n);

	// then their normals
	for (auto& n : theirTransform->TransformPoints(other->mesh_ptr->GetNormals()))
		normalsToCheck.push_back(n);
	
	// TODO edge pair normals

	// our transformed vertices
	auto ourVertices = ourTransform->TransformPoints(mesh_ptr->GetVerticesVec3());

	// their transformed vertices
	auto theirVertices = theirTransform->TransformPoints(other->mesh_ptr->GetVerticesVec3());

	// if we find a single plane without intersection, there is no overlap
	for (auto& n : normalsToCheck) {
		if (!OverlapOnAxis(ourVertices, theirVertices, n)) {
			return false;
		}
	}

	// otherwise there is overlap
	return true;

}



bool Collider::OverlapOnAxis(
	std::vector<glm::vec3>& va,
	std::vector<glm::vec3>& vb,
	glm::vec3& axis)
{
	float aMin = INFINITY, aMax = -INFINITY;
	for (auto& v : va) {
		auto dot = glm::dot(v, axis);
		aMin = std::min(aMin, dot);
		aMax = std::max(aMax, dot);
	}
	float bMin = INFINITY, bMax = -INFINITY;
	for (auto& v : vb) {
		auto dot = glm::dot(v, axis);
		bMin = std::min(bMin, dot);
		bMax = std::max(bMax, dot);
	}
	return aMin < bMax && aMax > bMin;

}
