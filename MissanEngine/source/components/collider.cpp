#include "components/collider.hpp"


using namespace missan;

// PUBLIC


Transform& Collider::GetTransform() {
	return *transform_ptr;
}

std::vector<glm::vec3> Collider::GetTranslatedVertices() {

	std::vector<glm::vec3> translatedVertices;
	std::vector<float> v = mesh_ptr->vertices;
	Transform& transform = *transform_ptr;
	glm::mat4 mat = transform.GetMatrix();

	for (int i = 0; i < v.size(); i += 3) {
		glm::vec4 w(v[0], v[1], v[2], 1.0f);
		glm::vec4 u = mat * w;
		translatedVertices.push_back({ u.x, u.y, u.z });
	}

	return translatedVertices;

}

bool Collider::OverlapsWith(Collider& other) {

	if (!isEnabled || !other.IsEnabled()) return false;

	// using separated axis theorem (SAT)
	// normals that needs to be tested:
	// face normals for A
	// + face normals for B
	// + face normals of all pairs of edges from A and B

	std::vector<glm::vec3> va, vb;
	va = GetTranslatedVertices();
	vb = other.GetTranslatedVertices();

	std::vector<glm::vec3> normals;

	// get normals for A
	auto aInds = mesh_ptr->indices;
	std::vector<glm::vec3> newNormals = CalcNormals(va, aInds);
	normals.insert(normals.end(), newNormals.begin(), newNormals.end());
	
	// normals for B
	auto bInds = other.GetMesh().indices;
	newNormals = CalcNormals(vb, bInds);
	normals.insert(normals.end(), newNormals.begin(), newNormals.end());

	// TODO, add normals from edge pairs...

	for (auto& n : normals) 
		if (!OverlapOnAxis(va, vb, n)) return false;
	



	return true;
}

void Collider::SetTransform(Transform& transform) {
	transform_ptr = &transform;
}

Mesh& Collider::GetMesh() {
	return *mesh_ptr;
}

std::vector<glm::vec3> Collider::CalcNormals(
	std::vector<glm::vec3>& vertices,
	std::vector<unsigned int>& indices)
{
	// using inefficient method which gets 
	// normals from each triangle. 
	std::vector<glm::vec3> normals;
	for (int i = 0; i < indices.size(); i += 3) {
		glm::vec3 v = vertices[indices[i]] + vertices[indices[i + 1]];
		glm::vec3 w = vertices[indices[i]] + vertices[indices[i + 2]];
		normals.push_back(glm::cross(v, w));
	}
	return normals;
}

bool Collider::OverlapOnAxis(
	std::vector<glm::vec3>& va,
	std::vector<glm::vec3>& vb,
	glm::vec3& axis)
{
	std::pair<float, float> shadowA = CalcProjMinMax(va, axis);
	std::pair<float, float> shadowB = CalcProjMinMax(vb, axis);

	return shadowA.first < shadowB.second
		&& shadowA.second > shadowB.first;
}

std::pair<float, float> Collider::CalcProjMinMax(
	std::vector<glm::vec3>& points, 
	glm::vec3& normal) 
{
	float min = INFINITY;
	float max = -INFINITY;

	for (auto& p : points) {
		float a = glm::dot(p, normal);
		if (a < min) min = a;
		if (a > max) max = a;
	}

	return { min, max };

}

void Collider::Enable(bool enable) {
	isEnabled = enable;
}

void Collider::SetMesh(Mesh& mesh) {
	mesh_ptr = &mesh;
}

bool Collider::IsEnabled() {
	return isEnabled;
}