#include "physics/collider.hpp"

#include "core/transform.hpp"

#include <vector>

#include <glm/vec3.hpp>

using namespace Missan;

// PUBLIC

// Returns a vector representing the shortest displacement requried to separate the 2 Colliders.
// The positive direction of the vector is from "other" to "this"
glm::vec3 Collider::OverlapsWith(Collider* other) {

	// The Separating axis Theorem states that 2 sets of points, forming convex shapes,
	// DO NOT overlap IF there exists an axis upon the ranges of their projected points
	// do not overlap. 
	
	std::vector<glm::vec3> normalsToCheck;

	// the amount of overlap, specifically the shortest displacement along some direction required to cancel the overlap
	float minimumOverlap = INFINITY;
	glm::vec3 displacement(0, 0, 0);

	Transform* ourTransform = GetGameObject().GetComponent<Transform>();
	Transform* theirTransform = other->GetGameObject().GetComponent<Transform>();



	// first we need our own transformed face-normals
	for (glm::vec3& n : ourTransform->TransformPoints(boundingBox.GetNormals()))
		normalsToCheck.push_back(n);

	// then their transformed normals
	for (glm::vec3& n : theirTransform->TransformPoints(other->boundingBox.GetNormals()))
		normalsToCheck.push_back(n);
	
	// and finally the normals of the planes formed by each pair of edges from each shape
	std::vector<glm::vec3> ourEdges = ourTransform->TransformPoints(boundingBox.GetEdgeVectors());
	std::vector<glm::vec3> theirEdges = theirTransform->TransformPoints(other->boundingBox.GetEdgeVectors());
	for (glm::vec3& ourEdge : ourEdges) {
		for (glm::vec3& theirEdge : theirEdges) {

			// but we don't care for pairs where the edges are too similar, say less than 10%
			float threshold = 0.1f;
			if (glm::dot(glm::normalize(ourEdge), glm::normalize(theirEdge)) > threshold)
				normalsToCheck.push_back(glm::cross(ourEdge, theirEdge));
		}
	}



	// our transformed vertices
	std::vector<glm::vec3> ourVertices = ourTransform->TransformPoints(boundingBox.GetVertices());

	// their transformed vertices
	std::vector<glm::vec3> theirVertices = theirTransform->TransformPoints(other->boundingBox.GetVertices());



	// if we find a single plane without intersection, there is no overlap
	for (glm::vec3& n : normalsToCheck) {
		
		// we find the minimum and maximum extents of our shadow when projecting
		// all our points onto the normal
		float ourMin = INFINITY, ourMax = -INFINITY;
		for (glm::vec3& v : ourVertices) {
			float dot = glm::dot(v, n);
			ourMin = std::min(ourMin, dot);
			ourMax = std::max(ourMax, dot);
		}

		// and the same for them
		float theirMin = INFINITY, theirMax = -INFINITY;
		for (glm::vec3& v : theirVertices) {
			float dot = glm::dot(v, n);
			theirMin = std::min(theirMin, dot);
			theirMax = std::max(theirMax, dot);
		}

		// check if the ranges overlap
		bool isOverlap = ourMin < theirMax && ourMax > theirMin;

		if (!isOverlap) {
			return glm::vec3(0, 0, 0);
		}
		else {


			float ourMid = ourMax - ourMin;
			float theirMid = theirMax - theirMin;
			float currentOverlap = ourMid - theirMid;

			if (abs(currentOverlap) < abs(minimumOverlap)) {
				minimumOverlap = currentOverlap;
				displacement = glm::normalize(n) * currentOverlap;
			}
			
		}
		
	}

	// otherwise there is overlap
	return displacement;

}



// PRIVATE

void Collider::Start() {
	Mesh* mesh = GetGameObject().GetComponent<Mesh>();
	if (mesh != nullptr) {
		auto ps = mesh->GetVerticesVec3();
		boundingBox.EncapsulatePoints(ps);
	}
}

