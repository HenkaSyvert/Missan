#include "transform.h"

#include <glm/gtc/matrix_transform.hpp> 

using namespace missan;

// PUBLIC
glm::mat4 Transform::GetMatrix() {
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.z), glm::vec3(0, 0, 1));
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.x), glm::vec3(1, 0, 0));
	
	
	matrix = glm::scale(matrix, scale);
	return matrix;
}


glm::vec3 Transform::GetBackwardVector() {
	return glm::normalize(GetMatrix()[2]);
}
glm::vec3 Transform::GetRightVector() {
	return glm::normalize(GetMatrix()[0]);
}
glm::vec3 Transform::GetUpVector() {
	return glm::normalize(GetMatrix()[1]);
}

