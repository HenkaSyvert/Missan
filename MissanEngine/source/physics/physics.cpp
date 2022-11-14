#include "physics/physics.hpp"

#include "engine.hpp"
#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/rigidbody.hpp"
#include "physics/collision.hpp"
#include "internal.hpp"

#include <glm/trigonometric.hpp>
#include <glm/glm.hpp>

#include <limits>
#include <vector>

using namespace Missan;
using namespace std;
using namespace glm;

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

bool SphereSphereCollision(Collider* a, Collider* b) {

	vec3 difference = a->transform->position - b->transform->position;
	float distance = length(difference);

	float aRadius = a->radius * a->transform->scale.x;
	float bRadius = b->radius * b->transform->scale.x;

	float separation = distance - aRadius - bRadius;
	return separation < 0;
}

bool AabbAabbCollision(Collider* a, Collider* b) {

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

	return distance.x < 0 || distance.y < 0 || distance.z < 0;

}

bool BoxSphereCollision(Collider* box, Collider* sphere) {

	vector<vec3> vertices = box->transform->TransformPoints(unitCube);
	for (auto axis : box->transform->axes) {

		float center = dot(sphere->transform->position, axis);

		float min = numeric_limits<float>::infinity();
		float max = -numeric_limits<float>::infinity();

		for (int i = 0; i < 8; i++) {

			float proj = dot(vertices[i], axis);
			min = proj < min ? proj : min;
			max = proj > max ? proj : max;

		}

		float totalSpan = glm::max(max, center + sphere->radius) - glm::min(min, center - sphere->radius);
		float spanSum = (max - min) + sphere->radius * 2;
		if (spanSum < totalSpan) return false;

	}

	return true;

}

bool BoxBoxCollision(Collider* a, Collider* b) {

	// for cuboid-cuboid collision, the axes to test are the 
	// face normals (which are the same as the transform axes)
	// and also all cross products of the edges of each cuboid 
	// (which happens to align with the face normals). 
	vector<vec3> axes;
	for (auto aAxis : a->transform->axes) {
		axes.push_back(aAxis);
		for (auto bAxis : b->transform->axes) {
			axes.push_back(bAxis);
			axes.push_back(cross(aAxis, bAxis));
		}
	}

	const vector<vec3> aVertices = a->transform->TransformPoints(unitCube);
	const vector<vec3> bVertices = b->transform->TransformPoints(unitCube);

	for (auto axis : axes) {

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

		if (totalSpan > spanSum) return false;

	}

	return true;

}

bool IsOverlapping(Collider* a, Collider* b) {

	if (a->shape == Collider::Shape::sphere) {
		if (b->shape == Collider::Shape::sphere) return SphereSphereCollision(a, b);
		else return BoxSphereCollision(b, a);
	}
	else {
		if (b->shape == Collider::Shape::sphere) return BoxSphereCollision(a, b);
		else return BoxBoxCollision(a, b);
	}

}




void ApplyForces() {

	for (RigidBody* rb : RigidBody::instances) {

		Transform* t = rb->gameObject->GetComponent<Transform>();

		if (rb->isAffectedByGravity)
			rb->AddImpulse(Physics::gravity / rb->mass);

		vec3 forces = rb->forces + rb->linearImpulse;
		vec3 torque = rb->torques + rb->angularImpulse;

		vec3 linearAcceleration = forces / Time::deltaTime / rb->mass;
		rb->linearVelocity += linearAcceleration * Time::deltaTime;
		rb->linearVelocity *= clamp(1.0f - rb->linearDrag * Time::deltaTime, 0.0f, 1.0f);
		t->position += rb->linearVelocity * Time::deltaTime;

		vec3 angularAcceleration = torque / Time::deltaTime / rb->inertiaTensor;
		rb->angularVelocity += angularAcceleration * Time::deltaTime;
		rb->angularVelocity *= clamp(1.0f - rb->angularDrag * Time::deltaTime, 0.0f, 1.0f);
		t->rotation += degrees(rb->angularVelocity) * Time::deltaTime;

		rb->linearImpulse = { 0,0,0 };
		rb->angularImpulse = { 0,0,0 };
	}
}

vector<Collision> collisions;

void HandleCollisions() {

	vector<Collider*>& colliders = Collider::instances;

	if (colliders.size() <= 1) return;

	for (unsigned int i = 0; i < colliders.size() - 1; i++) {
		Collider* ca = colliders[i];

		for (unsigned int j = i + 1; j < colliders.size(); j++) {
			Collider* cb = colliders[j];

			bool wasAlreadyOverlapping = false;
			int collisionIndex;
			for (size_t k = 0; k < collisions.size(); k++) {
				auto p = collisions[k];
				if (p.ourCollider == ca && p.otherCollider == cb || p.ourCollider == cb && p.otherCollider == ca) {
					wasAlreadyOverlapping = true;
					collisionIndex = k;
					break;
				}
			}

			if (IsOverlapping(ca, cb)) {
				if (!wasAlreadyOverlapping) {

					Collision collision;
					collision.ourCollider = ca;
					collision.otherCollider = cb;
					collisions.push_back(collision);

					for (auto* c : ca->gameObject->components) c->OnCollisionEnter(cb->gameObject);
					for (auto* c : cb->gameObject->components) c->OnCollisionEnter(ca->gameObject);
				}
				for (auto* c : ca->gameObject->components) c->OnCollisionStay(cb->gameObject);
				for (auto* c : cb->gameObject->components) c->OnCollisionStay(ca->gameObject);
			}
			else {
				if (wasAlreadyOverlapping) {
					for (auto* c : ca->gameObject->components) c->OnCollisionExit(cb->gameObject);
					for (auto* c : cb->gameObject->components) c->OnCollisionExit(ca->gameObject);

					collisions.erase(collisions.begin() + collisionIndex);
				}
			}
		}



	}


}

vec3 Physics::gravity = { 0.0f, -9.81f, 0.0f };

void PhysicsUpdate() {
	ApplyForces();
	HandleCollisions();
}


