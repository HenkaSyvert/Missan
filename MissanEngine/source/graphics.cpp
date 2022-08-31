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
Camera* Graphics::camera = nullptr;



Mesh::Mesh(int vaoId, const vector<float>& vs, const vector<unsigned int>& indices) {

	this->vaoId = vaoId;
	for (unsigned int i = 0; i < vs.size(); i += 3) vertices.push_back(vec3(vs[i], vs[i + 1], vs[i + 2]));
	for (unsigned int i = 0; i < indices.size(); i += 3) normals.push_back(cross(vertices[indices[i]], vertices[indices[i + 1]]));

}

void GraphicsInitialize() {
	shader = new ShaderProgram("resources/shaders/vertex.shader", "resources/shaders/fragment.shader");
}

void GraphicsUpdate() {
	vec4 clearColor = { .1,.1,.1,.1 };	// temp, should move to camera

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

	vector<Renderer*> renderers;
	auto& gameObjects = EcsGetGameObjects();
	for (auto* g : gameObjects) if (g->GetComponent<Renderer>()) renderers.push_back(g->GetComponent<Renderer>());
	for (auto r : renderers) Draw(r);
}

void Graphics::Draw(Renderer* renderer) {

	glUseProgram(shader->programId);

	if (!renderer->mesh) return;

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(renderer->mesh->vaoId);
	glEnableVertexAttribArray(0);
	mat4 transMat = renderer->gameObject->GetComponent<Transform>()->matrix;
	shader->SetMat4("u_model", transMat);
	mat4 view = inverse(camera->gameObject->GetComponent<Transform>()->matrix);
	shader->SetMat4("u_view", view);
	shader->SetMat4("u_proj", camera->projectionMatrix);
	
	Texture* texture = renderer->texture;
	if (texture) {
		glEnableVertexAttribArray(1);
		shader->SetInt("u_texture", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->textureId);
	}

	glDrawElements(GL_TRIANGLES, renderer->mesh->vertices.size() * 3, GL_UNSIGNED_INT, 0);

	if (texture) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(1);
	}

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
