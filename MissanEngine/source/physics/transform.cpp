#include "physics/transform.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"

using namespace Missan;
using namespace std;
using namespace glm;
using namespace ImGui;

void Transform::UpdateMatrix() {

	// order matters, must be translation-rotation-scale
	_matrix = mat4(1.0f);
	_matrix = translate(matrix, _position);
	
	// order matters, must be y-z-x
	_matrix = rotate(matrix, radians(_rotation.y), vec3(0, 1, 0));
	_matrix = rotate(matrix, radians(_rotation.z), vec3(0, 0, 1));
	_matrix = rotate(matrix, radians(_rotation.x), vec3(1, 0, 0));
	
	_matrix = glm::scale(_matrix, _scale);
	_invMat = glm::inverse(_matrix);
}

vec3 Transform::TransformPoint(vec3& point) {
	vec4 q(point, 1);
	q = _matrix * q;
	return vec3(q.x, q.y, q.z);
}

vector<vec3> Transform::TransformPoints(vector<vec3> points) {
	vector<vec3> ps;
	for (auto p : points)
		ps.push_back(TransformPoint(p));
	return ps;
}

void Transform::DisplayInInspector() {
	Text("Transform");
	DragFloat3("position", (float*)&_position);
	DragFloat3("rotation", (float*)&_rotation);
	DragFloat3("scale", (float*)&_scale);
	UpdateMatrix();
}