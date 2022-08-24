#include "boundingbox.hpp"

using namespace Missan;
using namespace std;
using namespace glm;

vector<vec3> BoundingBox::GetVertices() {

	vector<vec3> v;
	float x = size.x / 2;
	float y = size.y / 2;
	float z = size.z / 2;

	v.push_back({  x, -y, -z });
	v.push_back({  x, -y,  z });
	v.push_back({  x,  y, -z });
	v.push_back({  x,  y,  z });
	v.push_back({ -x, -y, -z });
	v.push_back({ -x, -y,  z });
	v.push_back({ -x,  y, -z });
	v.push_back({ -x,  y,  z });

	return v;
}

vector<vec3> BoundingBox::GetNormals() {
	vector<vec3> v;
	v.push_back({ 1,0,0 });
	v.push_back({ 0,1,0 });
	v.push_back({ 0,0,1 });
	return v;
}

vector<vec3> BoundingBox::GetEdgeVectors() {
	// Just happens to be the same
	return GetNormals();
}

void BoundingBox::EncapsulatePoints(vector<vec3>& points) {
	float x = 0;
	float y = 0;
	float z = 0;

	for (auto& p : points) {
		x = max(abs(p.x), x);
		y = max(abs(p.y), y);
		z = max(abs(p.z), z);
	}

	size = { 2 * x, 2 * y, 2 * z };
}


