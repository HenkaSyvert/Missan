#include "transform.hpp"

#include <glm/trigonometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Missan;
using namespace std;
using namespace glm;

void Transform::Update() {

	// order matters, must be translation-rotation-scale
	matrix = mat4(1.0f);
	matrix = translate(matrix, position);
	
	// order matters, must be y-z-x
	matrix = rotate(matrix, radians(rotationDeg.y), vec3(0, 1, 0));
	matrix = rotate(matrix, radians(rotationDeg.z), vec3(0, 0, 1));
	matrix = rotate(matrix, radians(rotationDeg.x), vec3(1, 0, 0));
	
	matrix = glm::scale(matrix, scale);
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

vec3 Transform::GetRightVector() {
	return normalize(matrix[0]);
}

vec3 Transform::GetUpVector() {
	return normalize(matrix[1]);
}

vec3 Transform::GetBackwardVector() {
	return normalize(matrix[2]);
}


