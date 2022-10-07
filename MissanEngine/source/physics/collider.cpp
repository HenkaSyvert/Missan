#include "physics/collider.hpp"

#include "physics/transform.hpp"
#include "graphics/mesh.hpp"

#include <vector>

#include <glm/vec3.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

// Returns a vector representing the shortest displacement requried to separate the 2 Colliders.
// The positive direction of the vector is from "other" to "this"
vec3 Collider::OverlapsWith(Collider& other) {

	// The Separating axis Theorem states that 2 sets of points, forming convex shapes,
	// DO NOT overlap IF there exists an axis upon which the ranges of their projected 
	// points do not overlap. 
	
	// the amount of overlap, specifically the shortest displacement along some direction required to cancel the overlap
	float minimumOverlap = INFINITY;
	vec3 displacement(0, 0, 0);

	Transform* transform = Component::Get<Transform>(gameObjectId);
	Transform* otherTransform = Component::Get<Transform>(other.gameObjectId);

	vector<vec3> normalsToCheck(transform->TransformPoints(boundingBox.GetNormals()));
	for (vec3& n : otherTransform->TransformPoints(other.boundingBox.GetNormals())) normalsToCheck.push_back(n);
	
	// and finally the normals of the planes formed by each pair of edges from each shape
	vector<vec3> ourEdges = transform->TransformPoints(boundingBox.GetEdgeVectors());
	vector<vec3> theirEdges = otherTransform->TransformPoints(other.boundingBox.GetEdgeVectors());
	for (vec3& ourEdge : ourEdges) {
		for (vec3& theirEdge : theirEdges) {

			// but we don't care for pairs where the edges are too similar, say less than 10%
			float threshold = 0.1f;
			if (dot(normalize(ourEdge), normalize(theirEdge)) > threshold)
				normalsToCheck.push_back(cross(ourEdge, theirEdge));
		}
	}

	vector<vec3> ourVertices = transform->TransformPoints(boundingBox.GetVertices());
	vector<vec3> theirVertices = otherTransform->TransformPoints(other.boundingBox.GetVertices());

	// if we find a single plane without intersection, there is no overlap
	for (vec3& n : normalsToCheck) {
		
		// we find the minimum and maximum extents of our shadow when projecting
		// all our points onto the normal
		float ourMin = INFINITY, ourMax = -INFINITY;
		for (vec3& v : ourVertices) {
			float dot = glm::dot(v, n);
			ourMin = std::min(ourMin, dot);
			ourMax = std::max(ourMax, dot);
		}

		// and the same for them
		float theirMin = INFINITY, theirMax = -INFINITY;
		for (vec3& v : theirVertices) {
			float dot = glm::dot(v, n);
			theirMin = std::min(theirMin, dot);
			theirMax = std::max(theirMax, dot);
		}

		// check if the ranges overlap
		bool isOverlap = ourMin < theirMax && ourMax > theirMin;

		if (!isOverlap) {
			return vec3(0, 0, 0);
		}
		else {
			float ourMid = ourMax - ourMin;
			float theirMid = theirMax - theirMin;
			float currentOverlap = ourMid - theirMid;

			if (abs(currentOverlap) < abs(minimumOverlap)) {
				minimumOverlap = currentOverlap;
				displacement = normalize(n) * currentOverlap;
			}	
		}	
	}

	// otherwise there is overlap
	return displacement;
}
