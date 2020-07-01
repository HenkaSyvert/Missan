#include "transform.h"

#include <glm/gtc/matrix_transform.hpp> 

using namespace missan;

// PUBLIC
glm::mat4 Transform::GetMatrix() {
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rotationDeg.z), glm::vec3(0, 0, 1));
	
	matrix = glm::scale(matrix, scale);
	return matrix;
}


glm::vec3 Transform::GetBackwardVector() {
	//glm::vec3 v;
	//v.x = cos(glm::radians(rotationDeg.y)) * cos(glm::radians(rotationDeg.x));
	//v.y = sin(glm::radians(rotationDeg.x));
	//v.z = sin(glm::radians(rotationDeg.y)) * cos(glm::radians(rotationDeg.x));
	//v = glm::normalize(v);
	//return v;
	return glm::normalize(GetMatrix()[2]);
}
glm::vec3 Transform::GetRightVector() {
	//glm::vec3 back = GetBackwardVector();
	//return glm::normalize(glm::cross())

	return glm::normalize(GetMatrix()[0]);
}
glm::vec3 Transform::GetUpVector() {
	return glm::normalize(GetMatrix()[1]);
}