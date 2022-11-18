#include "physics/transform.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

using namespace Missan;
using namespace std;
using namespace glm;
using namespace ImGui;

static void UpdateMatrix(Transform& t) {

	// order matters, must be translation-rotation-scale
	t.localToWorldMatrix = mat4(1.0f);
	t.localToWorldMatrix = translate(t.localToWorldMatrix, t.position);
	
	// order matters, must be y-z-x
	t.localToWorldMatrix = rotate(t.localToWorldMatrix, radians(t.rotation.y), vec3(0, 1, 0));
	t.localToWorldMatrix = rotate(t.localToWorldMatrix, radians(t.rotation.z), vec3(0, 0, 1));
	t.localToWorldMatrix = rotate(t.localToWorldMatrix, radians(t.rotation.x), vec3(1, 0, 0));
	
	t.localToWorldMatrix = glm::scale(t.localToWorldMatrix, t.scale);
	t.worldToLocalMatrix = glm::inverse(t.localToWorldMatrix);

	t.right = normalize(t.localToWorldMatrix[0]);
	t.up = normalize(t.localToWorldMatrix[1]);
	t.forward = -normalize(t.localToWorldMatrix[2]);

}

void Transform::Start() {
	UpdateMatrix(*this);
}

void Transform::Update() {
	UpdateMatrix(*this);
}

vec3 Transform::TransformPoint(vec3& point) {
	vec4 q(point, 1);
	q = localToWorldMatrix * q;
	return vec3(q.x, q.y, q.z);
}

vector<vec3> Transform::TransformPoints(vector<vec3> points) {
	vector<vec3> ps;
	for (auto& p : points)
		ps.push_back(TransformPoint(p));
	return ps;
}

void Transform::DisplayInInspector() {
	if (CollapsingHeader("Transform")) {
		DragFloat3("position", (float*)&position, 0.01f);
		DragFloat3("rotation", (float*)&rotation, 0.1f);
		DragFloat3("scale", (float*)&scale, 0.01f);
	}
}