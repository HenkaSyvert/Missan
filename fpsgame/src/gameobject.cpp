#include "gameobject.h"

using namespace missan;

// PUBLIC
Transform& GameObject::GetTransform() {
	return transform;
}

Model& GameObject::GetModel() {
	return *model_ptr;
}

GameObject::GameObject(Model& model, glm::vec3 pos, glm::vec3 rot) {
	model_ptr = &model;
	transform.position = pos;
	transform.rotationDeg = rot;
}