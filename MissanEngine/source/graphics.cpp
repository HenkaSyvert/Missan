#include "graphics.hpp"

#include "transform.hpp"
#include "internal.hpp"
#include "gameobject.hpp"
#include "component.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

using namespace Missan;
using namespace std;
using namespace glm;
using namespace Graphics;

ShaderProgram* Graphics::shader = nullptr;

Mesh::Mesh(int vaoId, int elementCount) {
	this->vaoId = vaoId;
	this->elementCount = elementCount;
}

void GraphicsInitialize() {
	shader = new ShaderProgram("resources/shaders/vertex.shader", "resources/shaders/fragment.shader");
}

void GraphicsUpdate() {
	vec4 clearColor = Camera::main->clearColor;
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glUseProgram(shader->programId);

	vector<Renderer*> renderers;
	auto& gameObjects = EcsGetGameObjects();
	for (auto* g : gameObjects) if (g->GetComponent<Renderer>()) renderers.push_back(g->GetComponent<Renderer>());

	for (auto renderer : renderers) {

		if (!renderer->mesh) continue;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(renderer->mesh->vaoId);
		glEnableVertexAttribArray(0);
		mat4 transMat = renderer->gameObject->GetComponent<Transform>()->matrix;
		shader->SetMat4("u_model", transMat);
		mat4 view = inverse(Camera::main->gameObject->GetComponent<Transform>()->matrix);
		shader->SetMat4("u_view", view);
		shader->SetMat4("u_proj", Camera::main->projectionMatrix);

		Texture* texture = renderer->texture;
		if (texture) {
			glEnableVertexAttribArray(1);
			shader->SetInt("u_texture", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->id);
		}

		glDrawElements(GL_TRIANGLES, renderer->mesh->elementCount, GL_UNSIGNED_INT, 0);

		if (texture) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(1);
		}

		glDisableVertexAttribArray(0);

	}
}
