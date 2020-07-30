#include "physics/collider.hpp"

#include "missanpch.hpp"
#include "core/transform.hpp"

using namespace Missan;

// PUBLIC

// returns the amount of overlap, return 0 if there is no overlap
glm::vec3 Collider::OverlapsWith(Collider* other) {

	// The Separating axis Theorem: 2 sets of points, forming convex bodies, 
	// DO NOT overlap IF you can find a separating plane between them. 
	// which is done by projecting the points from both sets onto the normals
	// of all possible separating planes and check if their shadows overlap.
	
	std::vector<glm::vec3> normalsToCheck;

	// the amount of overlap, specifically the shortest displacement along some direction required to cancel the overlap
	float displacementMagnitude = INFINITY;
	glm::vec3 displacementDirection;

	auto ourTransform = GetGameObject().GetComponent<Transform>();
	auto theirTransform = other->GetGameObject().GetComponent<Transform>();



	// first we need our own transformed face-normals
	for (auto& n : ourTransform->TransformPoints(boundingBox.GetNormals()))
		normalsToCheck.push_back(n);

	// then their transformed normals
	for (auto& n : theirTransform->TransformPoints(other->boundingBox.GetNormals()))
		normalsToCheck.push_back(n);
	
	// and finally the normals of the planes formed by each pair of edges from each shape
	auto ourEdges = ourTransform->TransformPoints(boundingBox.GetEdgeVectors());
	auto theirEdges = theirTransform->TransformPoints(other->boundingBox.GetEdgeVectors());
	for (auto& ourEdge : ourEdges) {
		for (auto& theirEdge : theirEdges) {

			// but we don't care for pairs where the edges are too similar, say less than 10%
			float threshold = 0.1f;
			if (glm::dot(glm::normalize(ourEdge), glm::normalize(theirEdge)) > threshold)
				normalsToCheck.push_back(glm::cross(ourEdge, theirEdge));
		}
	}



	// our transformed vertices
	auto ourVertices = ourTransform->TransformPoints(boundingBox.GetVertices());

	// their transformed vertices
	auto theirVertices = theirTransform->TransformPoints(other->boundingBox.GetVertices());



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

		// keep track of the minimum displacement required to cancel the overlap
		float newDisplacement = std::min(std::min(ourMax, theirMax) - std::max(ourMin, theirMin), displacementMagnitude);
		if (newDisplacement < displacementMagnitude) {
			displacementMagnitude = newDisplacement;
			displacementDirection = n;
		}

		// check if the ranges overlap
		bool overlapOnAxis = ourMin < theirMax&& ourMax > theirMin;

		if (!overlapOnAxis) {
			return glm::vec3(0,0,0);
		}
	}

	// otherwise there is overlap
	return glm::normalize(displacementDirection) * displacementMagnitude;

}



// PRIVATE

void Collider::Start() {
	Mesh* mesh = GetGameObject().GetComponent<Mesh>();
	if (mesh != nullptr) {
		auto ps = mesh->GetVerticesVec3();
		boundingBox.EncapsulatePoints(ps);
	}
}

