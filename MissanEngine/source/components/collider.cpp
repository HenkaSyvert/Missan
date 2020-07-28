#include "components/collider.hpp"

#include "components/transform.hpp"

#include <algorithm>	// std::min, std::max

using namespace missan;

// PUBLIC



float Collider::OverlapsWith(Collider* other) {

	// The Separating axis Theorem: 2 sets of points, forming convex bodies, 
	// DO NOT overlap IF you can find a separating plane between them. 
	// which is done by projecting the points from both sets onto the normals
	// of all possible separating planes and check if their shadows overlap.
	
	std::vector<glm::vec3> normalsToCheck;

	// the amount of overlap
	float overlap = INFINITY;

	auto ourTransform = GetGameObject().GetComponent<Transform>();
	auto theirTransform = other->GetGameObject().GetComponent<Transform>();

	// first we need our own transformed face-normals
	for (auto& n : ourTransform->TransformPoints(mesh_ptr->GetNormals()))
		normalsToCheck.push_back(n);

	// then their normals
	for (auto& n : theirTransform->TransformPoints(other->mesh_ptr->GetNormals()))
		normalsToCheck.push_back(n);
	
	// and finally the normals of the planes formed by each pair of edges from each shape
	auto ourEdges = ourTransform->TransformPoints(mesh_ptr->GetEdgeDirections());
	auto theirEdges = theirTransform->TransformPoints(other->mesh_ptr->GetEdgeDirections());
	int ignoredNormals = 0;
	for (auto& ourEdge : ourEdges) {
		for (auto& theirEdge : theirEdges) {

			// but we don't care for pairs where the edges are too similar, say less than 10%
			float threshold = 0.1f;
			if (glm::dot(glm::normalize(ourEdge), glm::normalize(theirEdge)) > threshold)
				normalsToCheck.push_back(glm::cross(ourEdge, theirEdge));
			else ignoredNormals++;
		}
	}

	//std::cout << dfg;
	//std::cin.get();

	// our transformed vertices
	auto ourVertices = ourTransform->TransformPoints(mesh_ptr->GetVerticesVec3());

	// their transformed vertices
	auto theirVertices = theirTransform->TransformPoints(other->mesh_ptr->GetVerticesVec3());

	// if we find a single plane without intersection, there is no overlap
	for (auto& n : normalsToCheck) {
		
		// we find the minimum and maximum extents of our shadow when projecting
		// all our points onto the normal
		float ourMin = INFINITY, ourMax = -INFINITY;
		for (auto& v : ourVertices) {
			auto dot = glm::dot(v, n);
			ourMin = std::min(ourMin, dot);
			ourMax = std::max(ourMax, dot);
		}

		// and the same for them
		float theirMin = INFINITY, theirMax = -INFINITY;
		for (auto& v : theirVertices) {
			auto dot = glm::dot(v, n);
			theirMin = std::min(theirMin, dot);
			theirMax = std::max(theirMax, dot);
		}

		overlap = std::min(std::min(ourMax, theirMax) - std::max(ourMin, theirMin), overlap);

		// check if the ranges overlap
		bool overlapOnAxis = ourMin < theirMax&& ourMax > theirMin;

		if (!overlapOnAxis) {

			return 0;
		}
	}

	// otherwise there is overlap
	return overlap;

}
