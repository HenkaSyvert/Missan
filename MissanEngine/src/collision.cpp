#include "transform.hpp"
#include "collider.hpp"
#include "collision.hpp"
#include "engine.hpp"
#include "internal.hpp"
#include "rigidbody.hpp"

#include <vector>
#include <limits>

using namespace Missan;
using namespace std;
using namespace glm;



vector<pair<Collision, Collision>> oldCollisions;

const vector<vec3> unitCube = {
	{0.5, 0.5, 0.5},
	{0.5, 0.5, -.5},
	{0.5, -.5, 0.5},
	{0.5, -.5, -.5},
	{-.5, 0.5, 0.5},
	{-.5, 0.5, -.5},
	{-.5, -.5, 0.5},
	{-.5, -.5, -.5}
};


// these contact point finding functions always return contact points from the perspective of the first collider. 

bool TestSphereSphereCollision(Collider* a, Collider* b, vector<ContactPoint>& contactPoints) {

	vec3 difference = a->transform->position - b->transform->position;
	float distance = length(difference);

	float aScale = glm::max(glm::max(a->transform->scale.x, a->transform->scale.y), a->transform->scale.z);
	float bScale = glm::max(glm::max(b->transform->scale.x, b->transform->scale.y), b->transform->scale.z);

	float aRadius = a->radius * aScale;
	float bRadius = b->radius * bScale;

	float separation = distance - aRadius - bRadius;

	if (separation < 0) {
		ContactPoint p;
		p.separation = separation;
		p.normal = normalize(difference);
		p.point = b->transform->position + difference / 2.0f;
		contactPoints.push_back(p);
		return true;
	}
	else return false;

}

Collision AabbAabbCollision(Collider* a, Collider* b) {

	// since AABB collision is supposed to be a cheap detection for potential collisions,
	// and since sphere colliders grow to max(scale x/y/z) aabb also grows this way. 
	float aScale = glm::max(glm::max(a->transform->scale.x, a->transform->scale.y), a->transform->scale.z);
	float bScale = glm::max(glm::max(b->transform->scale.x, b->transform->scale.y), b->transform->scale.z);

	vec3 aPos = a->transform->position;
	vec3 bPos = b->transform->position;

	vec3 aMin = aPos - a->size / 2.0f * aScale;
	vec3 aMax = aPos + a->size / 2.0f * aScale;
	vec3 bMin = bPos - b->size / 2.0f * bScale;
	vec3 bMax = bPos + b->size / 2.0f * bScale;

	vec3 distance = {
		aPos.x < bPos.x ? bMin.x - aMax.x : aMin.x - bMax.x,
		aPos.y < bPos.y ? bMin.y - aMax.y : aMin.y - bMax.y,
		aPos.z < bPos.z ? bMin.z - aMax.z : aMin.z - bMax.z
	};

	//return distance.x < 0 || distance.y < 0 || distance.z < 0;
	return Collision();

}

bool TestBoxSphereCollision(Collider* box, Collider* sphere, vector<ContactPoint>& contactPoints) {

	vector<vec3> axes;
	for (auto axis : box->transform->axes) axes.push_back(axis);
	axes.push_back(normalize(box->transform->position - sphere->transform->position));

	vector<vec3> vertices = box->transform->TransformPoints(unitCube);

	bool isOverlapping = true;

	for (const auto& axis : axes) {

		float min = numeric_limits<float>::infinity();
		float max = -numeric_limits<float>::infinity();

		for (int i = 0; i < 8; i++) {

			float proj = dot(vertices[i], axis);
			min = proj < min ? proj : min;
			max = proj > max ? proj : max;

		}

		float center = dot(sphere->transform->position, axis);

		float totalSpan = glm::max(max, center + sphere->radius) - glm::min(min, center - sphere->radius);
		float spanSum = (max - min) + sphere->radius * 2;
		float separation = totalSpan - spanSum;

		if (separation > 0) {
			ContactPoint p;
			p.separation = separation;
			p.normal = axis;	// these all SHOULD already be normalized
			p.point = box->transform->position + p.normal * separation;
			contactPoints.push_back(p);
			isOverlapping = false;
		}
	}

	return isOverlapping;

}

bool TestBoxBoxCollision(Collider* a, Collider* b, vector<ContactPoint>& contactPoints) {

	// for cuboid-cuboid collision, the axes to test are the 
	// face normals (which are the same as the transform axes)
	// and also all cross products of the edges of each cuboid 
	// (which happens to align with the face normals). 
	vector<vec3> axes;
	for (const auto& aAxis : a->transform->axes) {
		axes.push_back(aAxis);
		for (const auto& bAxis : b->transform->axes) {
			axes.push_back(normalize(cross(aAxis, bAxis)));
		}
	}
	for (const auto& axis : b->transform->axes) axes.push_back(axis);

	const vector<vec3> aVertices = a->transform->TransformPoints(unitCube);
	const vector<vec3> bVertices = b->transform->TransformPoints(unitCube);

	bool isOverlapping = true;

	for (const auto& axis : axes) {

		float aMin = numeric_limits<float>::infinity();
		float aMax = -numeric_limits<float>::infinity();
		float bMin = numeric_limits<float>::infinity();
		float bMax = -numeric_limits<float>::infinity();

		// go through each vertex and project onto axis to find min and max
		for (int i = 0; i < 8; i++) {

			float aProj = dot(aVertices[i], axis);
			float bProj = dot(bVertices[i], axis);

			aMin = aProj < aMin ? aProj : aMin;
			aMax = aProj > aMax ? aProj : aMax;

			bMin = bProj < bMin ? bProj : bMin;
			bMax = bProj > bMax ? bProj : bMax;

		}

		float totalSpan = glm::max(aMax, bMax) - glm::min(aMin, bMin);
		float spanSum = (aMax - aMin) + (bMax - bMin);
		float separation = totalSpan - spanSum;

		if (separation > 0) {
			ContactPoint p;
			p.separation = separation;
			p.normal = axis;	// these should all be normalized already
			//p.point = 
			contactPoints.push_back(p);
			isOverlapping = false;
		}

	}

	return isOverlapping;

}

Collision TestCollision(Collider* a, Collider* b, bool& isOverlap) {

	Collision collision;

	if (a->shape == Collider::Shape::Sphere) {
		if (b->shape == Collider::Shape::Sphere) isOverlap = TestSphereSphereCollision(a, b, collision.contactPoints);
		else isOverlap = TestBoxSphereCollision(b, a, collision.contactPoints);
	}
	else {
		if (b->shape == Collider::Shape::Sphere) isOverlap = TestBoxSphereCollision(a, b, collision.contactPoints);
		else isOverlap = TestBoxBoxCollision(a, b, collision.contactPoints);
	}

	return collision;

}



void DetectCollisions() {

	vector<pair<Collision, Collision>> newCollisions;

	vector<Collider*>& colliders = Collider::instances;
	if (colliders.size() <= 1) return;

	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];

			bool wasAlreadyOverlapping = false;
			pair<Collision, Collision>* oldCollisionPair = nullptr;
			for (size_t k = 0; k < oldCollisions.size(); k++) {
				auto& p = oldCollisions[k];
				if (p.first.collider == ca && p.second.collider == cb || p.first.collider == cb && p.second.collider == ca) {
					wasAlreadyOverlapping = true;
					oldCollisionPair = &p;
					break;
				}
			}

			bool isOverlap;
			// Collision class (and its contact points) describe a collision from the 
			// perspective of one of the colliders, so we need to mirror the collision
			// for object B later. 
			Collision aCollision = TestCollision(ca, cb, isOverlap);

			if (isOverlap) {

				Collision bCollision(aCollision);
				bCollision.transform = ca->transform;
				bCollision.collider = ca;
				bCollision.gameObject = ca->gameObject;
				bCollision.rigidBody = ca->GetComponent<RigidBody>();
				for (auto& p : bCollision.contactPoints) p.normal *= -1;			

				aCollision.collider = cb;
				aCollision.transform = cb->transform;
				aCollision.gameObject = cb->gameObject;
				aCollision.rigidBody = cb->GetComponent<RigidBody>();

				// apply forces and such only happens if both colliders have rigid bodies
				if (aCollision.rigidBody && bCollision.rigidBody) {
					
					aCollision.relativeVelocity = aCollision.rigidBody->linearVelocity - bCollision.rigidBody->linearVelocity;
					bCollision.relativeVelocity = -aCollision.relativeVelocity;

					vec3 forceSum = { 0, 0, 0 };
					for (auto& p : aCollision.contactPoints) forceSum += p.normal * p.separation;

					aCollision.impulse = forceSum * Time::deltaTime;
					bCollision.impulse = -aCollision.impulse;


				}

				newCollisions.push_back({aCollision, bCollision});

				if (!wasAlreadyOverlapping) {

					ca->gameObject->OnCollisionEnter(aCollision);
					cb->gameObject->OnCollisionEnter(bCollision);
				}
				ca->gameObject->OnCollisionStay(aCollision);
				cb->gameObject->OnCollisionStay(bCollision);
			}
			else {
				if (wasAlreadyOverlapping) {
					oldCollisionPair->first.gameObject->OnCollisionExit(oldCollisionPair->second);
					oldCollisionPair->second.gameObject->OnCollisionExit(oldCollisionPair->first);
				}
			}
		}
	}

	oldCollisions = newCollisions;

}



