#include "graphics.hpp"

#include "transform.hpp"
#include "internal.hpp"
#include "gameobject.hpp"
#include "component.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>


using namespace Missan;
using namespace glm;

static ShaderProgram* standardShader = nullptr;
static Camera* camera_ptr = nullptr;



void GraphicsInitialize() {
	standardShader = new ShaderProgram("vertex.shader", "fragment.shader");
}

void GraphicsUpdate() {
	vec4 clearColor = { .1,.1,.1,.1 };	// temp, should move to camera

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

	auto& gameObjects = EcsGetGameObjects();
	for (auto* g : gameObjects) for (auto* c : g->components) c->OnRender();
}

void Graphics::SetCamera(Camera& camera) {
	camera_ptr = &camera;
}

void Graphics::Draw(Renderer* renderer) {

	ShaderProgram& shader = *standardShader;
	shader.Use();

	Mesh& mesh = *renderer->mesh_ptr;
	if (&mesh == nullptr) return;
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(mesh.vaoID);
		glEnableVertexAttribArray(0);
		mat4 transMat = renderer->gameObject->GetComponent<Transform>()->GetMatrix();
		shader.SetMat4("u_model", transMat);
		mat4 view = inverse(camera_ptr->gameObject->GetComponent<Transform>()->GetMatrix());
		shader.SetMat4("u_view", view);
		mat4 projMat = camera_ptr->GetProjectionMatrix();
		shader.SetMat4("u_proj", projMat);
	}

	Texture& texture = *renderer->texture_ptr;
	bool hasTexture;
	if (&texture == nullptr) hasTexture = false;
	else {
		hasTexture = true;
		glEnableVertexAttribArray(1);
		shader.SetInt("u_texture", 0);
		texture.Bind();
	}

	glDrawElements(GL_TRIANGLES, mesh.vertices.size(), GL_UNSIGNED_INT, 0);

	if (hasTexture) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(1);
	}

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}
