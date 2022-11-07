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
	t.matrix = mat4(1.0f);
	t.matrix = translate(t.matrix, t.position);
	
	// order matters, must be y-z-x
	t.matrix = rotate(t.matrix, radians(t.rotation.y), vec3(0, 1, 0));
	t.matrix = rotate(t.matrix, radians(t.rotation.z), vec3(0, 0, 1));
	t.matrix = rotate(t.matrix, radians(t.rotation.x), vec3(1, 0, 0));
	
	t.matrix = glm::scale(t.matrix, t.scale);
	t.inverseMatrix = glm::inverse(t.matrix);

	t.right = normalize(t.matrix[0]); 
	t.up = normalize(t.matrix[1]); 
	t.forward = -normalize(t.matrix[2]); 

}

void Transform::Start() {
	UpdateMatrix(*this);
}

void Transform::Update() {
	UpdateMatrix(*this);
}

vec3 Transform::TransformPoint(vec3& point) {
	vec4 q(point, 1);
	q = matrix * q;
	return vec3(q.x, q.y, q.z);
}

vector<vec3> Transform::TransformPoints(vector<vec3> points) {
	vector<vec3> ps;
	for (auto p : points)
		ps.push_back(TransformPoint(p));
	return ps;
}

void Transform::DisplayInInspector() {
	if (CollapsingHeader("Transform")) {
		DragFloat3("position", (float*)&position);
		DragFloat3("rotation", (float*)&rotation);
		DragFloat3("scale", (float*)&scale);
	}
}