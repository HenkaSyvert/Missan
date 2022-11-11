#include "physics/collider.hpp"

#include "physics/transform.hpp"
#include "graphics/mesh.hpp"
#include "graphics/renderer.hpp"

#include <vector>

#include <glm/vec3.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

float CalcSphereToSphereDistance(Collider* a, Collider* b) {

	Transform* aTransform = a->gameObject->GetComponent<Transform>();
	Transform* bTransform = b->gameObject->GetComponent<Transform>();

	vec3 difference = aTransform->position - bTransform->position;

	float distance = length(difference);
	
	// not really sure how to do this, so I just use x component of scale to scale the sphere. 
	float aRadius = a->size.x * aTransform->scale.x;
	float bRadius = b->size.x * bTransform->scale.x;

	return distance - aRadius - bRadius;

}

// AABB (axis aligned bounding box) does not take rotation into account. 
// returns overlap along x,y,z axes. 
vec3 CalcAabbToAabbDistance(Collider* a, Collider* b) {

	Transform* aTransform = a->gameObject->GetComponent<Transform>();
	Transform* bTransform = b->gameObject->GetComponent<Transform>();

	vec3 aPos = aTransform->position;
	vec3 bPos = bTransform->position;

	vec3 aMin = aPos - a->size / 2.0f * aTransform->scale;
	vec3 aMax = aPos + a->size / 2.0f * aTransform->scale;
	vec3 bMin = bPos - b->size / 2.0f * bTransform->scale;
	vec3 bMax = bPos + b->size / 2.0f * bTransform->scale;

	//cout << "amin: " << aMin.x << ", amax: " << aMax.x << ", bmin: " << bMin.x << ", bmax: " << bMax.x << "\n";

	vec3 distance = {
		aPos.x < bPos.x ? bMin.x - aMax.x : aMin.x - bMax.x,
		aPos.y < bPos.y ? bMin.y - aMax.y : aMin.y - bMax.y,
		aPos.z < bPos.z ? bMin.z - aMax.z : aMin.z - bMax.z
	};

	//std::cout << "distance: " << distance.x << "\n";
	return distance;

}

// Returns a vector representing the shortest displacement requried to separate the 2 Colliders.
// The positive direction of the vector is from "other" to "this"
float Collider::OverlapsWith(Collider* other) {

	if (shape == Shape::sphere && other->shape == Shape::sphere) {
		return CalcSphereToSphereDistance(this, other);
	}
	else if (shape == Shape::aabb && other->shape == Shape::aabb) {
		vec3 v = CalcAabbToAabbDistance(this, other);
		if (v.x < 0 && v.y < 0 && v.z < 0) return v.x;
		return 1.0f;
	}

	// The Separating axis Theorem states that 2 sets of points, forming convex shapes,
	// DO NOT overlap IF there exists an axis upon which the ranges of their projected 
	// points do not overlap. 
	
	// the amount of overlap, specifically the shortest displacement along some direction required to cancel the overlap
	float minimumOverlap = INFINITY;
	vec3 displacement(0, 0, 0);

	vector<vec3> normalsToCheck(transform->TransformPoints(GetNormals()));
	for (vec3& n : other->transform->TransformPoints(other->GetNormals())) normalsToCheck.push_back(n);
	
	// and finally the normals of the planes formed by each pair of edges from each shape
	vector<vec3> ourEdges = transform->TransformPoints(GetEdgeVectors());
	vector<vec3> theirEdges = other->transform->TransformPoints(other->GetEdgeVectors());
	for (vec3& ourEdge : ourEdges) {
		for (vec3& theirEdge : theirEdges) {

			// but we don't care for pairs where the edges are too similar, say less than 10%
			float threshold = 0.1f;
			if (dot(normalize(ourEdge), normalize(theirEdge)) > threshold)
				normalsToCheck.push_back(cross(ourEdge, theirEdge));
		}
	}

	vector<vec3> ourVertices = transform->TransformPoints(GetVertices());
	vector<vec3> theirVertices = other->transform->TransformPoints(other->GetVertices());

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
			return false;
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
	return true;
}

void Collider::Start() {
	transform = gameObject->GetComponent<Transform>();
	Mesh* mesh = gameObject->GetComponent<Mesh>();
}

void Collider::OnCollisionEnter(GameObject* other) {
	cout << gameObject->name << ".OnCollisionEnter(" << other->name << ")\n";
}

void Collider::OnCollisionStay(GameObject* other) {
	cout << gameObject->name << ".OnCollisionStay(" << other->name << ")\n";
	isColliding = true;
	gameObject->GetComponent<Renderer>()->material->ambient = Color::red;
}

void Collider::OnCollisionExit(GameObject* other) {
	cout << gameObject->name << ".OnCollisionExit(" << other->name << ")\n";
	isColliding = false;
	gameObject->GetComponent<Renderer>()->material->ambient = Color::green;
}


void Collider::DisplayInInspector() {

	using namespace ImGui;
	if (CollapsingHeader("Collider")) {
		DragFloat3("size", (float*)&size, 0.01f);
		Checkbox("Is Colliding?", &isColliding);
	}

}