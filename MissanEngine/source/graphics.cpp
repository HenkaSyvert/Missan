#include "graphics.hpp"

#include <glm/glm.hpp>

#include <iostream>

using namespace missan;

namespace {

	ShaderProgram* standardShader_ = nullptr;
	Camera* camera_ptr = nullptr;
}


// PUBLIC
void Graphics::Initialize() {

	standardShader_ = new ShaderProgram("standard.vs", "standard.fs");
	

}

void Graphics::Prepare() {
	glm::vec4 clearColor = { .1,.1,.1,.1 };	// temp, should move to camera

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void Graphics::SetCamera(Camera& camera) {
	camera_ptr = &camera;
}

void Graphics::Draw(Renderer* renderer) {

	ShaderProgram& shader = Graphics::GetStandardShader();
	shader.Use();

	Mesh& mesh = *renderer->mesh_ptr;
	if (&mesh == nullptr) return;
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(mesh.vaoID);
		glEnableVertexAttribArray(0);
		glm::mat4 transMat = renderer->GetGameObject().GetComponent<Transform>()->GetMatrix();
		shader.SetMat4("u_model", transMat);
		glm::mat4 view = glm::inverse(camera_ptr->GetGameObject().GetComponent<Transform>()->GetMatrix());
		shader.SetMat4("u_view", view);
		glm::mat4 projMat = camera_ptr->GetProjectionMatrix();
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

ShaderProgram& Graphics::GetStandardShader() {
	return *standardShader_;
}

