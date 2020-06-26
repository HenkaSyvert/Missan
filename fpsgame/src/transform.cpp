#include "transform.h"

#include <glm/gtc/matrix_transform.hpp> 

using namespace missan;

// PUBLIC
glm::mat4 Transform::GetMatrix() {
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, position);
	matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, scale);
	return matrix;
}
