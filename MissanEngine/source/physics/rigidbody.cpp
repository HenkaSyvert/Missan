#include "physics/rigidbody.hpp"

#include "physics/transform.hpp"
#include "physics/collider.hpp"
#include "physics/physics.hpp"
#include "graphics/renderer.hpp"

#include <iostream>

using namespace Missan;
using namespace std;
using namespace glm;

void RigidBody::Start() {


	// currently rigidbodies only work with box colliders
	auto s = vec3(1, 1, 1);
	inertiaTensor =  {s.y* s.y + s.z * s.z, s.x* s.x + s.z * s.z, s.x* s.x + s.y * s.y};
	inertiaTensor *= mass / 12.0f;

	collider = GetComponent<Collider>();

}


void RigidBody::AddForce(vec3 newForce, vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		newForce = transform->TransformPoint(newForce);
		point = transform->TransformPoint(point);
	}
	forces += newForce;
	torques += cross(point, newForce);
}

void RigidBody::AddImpulse(vec3 impulse, vec3 point, bool useLocalSpace) {
	if (useLocalSpace) {
		impulse = transform->TransformPoint(impulse);
		point = transform->TransformPoint(point);
	}
	linearImpulse += impulse;
	angularImpulse += cross(point, impulse);
}


void RigidBody::DisplayInInspector() {

	using namespace ImGui;
	ShowDemoWindow();

	if (CollapsingHeader("Rigid Body")) {
		SliderFloat("Mass (kg)", &mass, .01f, 10000);
		DragFloat3("Linear Velocity", (float*)&linearVelocity);
		SliderFloat("Linear Drag", &linearDrag, 0, 1000);
		DragFloat3("Inertia Tensor", (float*)&inertiaTensor);
		DragFloat3("Angular Velocity", (float*)&angularVelocity);
		SliderFloat("Angular Drag", &angularDrag, 0, 1000);
		DragFloat3("forces", (float*)&forces);
		DragFloat3("Torques", (float*)&torques);
		Checkbox("use gravity", &isAffectedByGravity);
		DragFloat3("Linear Impulse", (float*)&linearImpulse);
		DragFloat3("Angular Impulse", (float*)&angularImpulse);

	}

}


void RigidBody::OnCollisionEnter(Collision collision) {

	// TODO: what point to apply impulse to?.. average of all contact points?
	AddImpulse(collision.impulse, collision.contactPoints[0].point, true);

}