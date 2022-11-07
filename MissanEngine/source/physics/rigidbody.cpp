#include "physics/rigidbody.hpp"

#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/physics.hpp"

#include <iostream>

using namespace Missan;
using namespace std;
using namespace glm;

void RigidBody::Start() {
	auto* c = gameObject->GetComponent<Collider>();
	if (c == nullptr) {
		cout << "RigidBody requires Collider Component!\n";
		exit(EXIT_FAILURE);
	}

	// currently rigidbodies only work with box colliders
	auto s = c->boundingBox.size;
	inertiaTensor =  {s.y* s.y + s.z * s.z, s.x* s.x + s.z * s.z, s.x* s.x + s.y * s.y};
	inertiaTensor *= mass / 12.0f;

}


void RigidBody::AddForce(vec3 newForce, vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		auto* t = gameObject->GetComponent<Transform>();
		newForce = t->TransformPoint(newForce);
		point = t->TransformPoint(point);
	}
	forces += newForce;
	torques += cross(point, newForce);
}

void RigidBody::AddImpulse(vec3 impulse, vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		auto* t = gameObject->GetComponent<Transform>();
		impulse = t->TransformPoint(impulse);
		point = t->TransformPoint(point);
	}
	linearImpulse += impulse;
	angularImpulse += cross(point, impulse);
}


void RigidBody::DisplayInInspector() {

	using namespace ImGui;
	ShowDemoWindow();

	if (CollapsingHeader("Rigid Body")) {
		SliderFloat("Mass (kg)", &mass, 0, 10000);
		DragFloat3("Linear Velocity", (float*)&linearVelocity);
		DragFloat3("Inertia Tensor", (float*)&inertiaTensor);
		DragFloat3("Angular Velocity", (float*)&angularVelocity);
		DragFloat3("forces", (float*)&forces);
		DragFloat3("Torques", (float*)&torques);
		Checkbox("use gravity", &isAffectedByGravity);
		DragFloat3("Linear Impulse", (float*)&linearImpulse);
		DragFloat3("Angular Impulse", (float*)&angularImpulse);
	}

}