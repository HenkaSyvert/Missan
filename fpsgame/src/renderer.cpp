#include "renderer.hpp"

#include <iostream>

using namespace missan;

// PUBLIC
Renderer::Renderer(ShaderProgram& shader, Camera& camera) {
	shader_ptr = &shader;
	camera_ptr = &camera;
}

void Renderer::Prepare() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

void Renderer::SetClearColor(glm::vec4 color) {
	clearColor = color;
}

void Renderer::RenderCollider(Collider& collider) {

	Mesh& mesh = collider.GetMesh();
	if (&mesh == nullptr) return;

	glColor3ub(0, 255, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	

	shader_ptr->Use();

	glm::mat4 transMat = collider.GetTransform().GetMatrix();
	shader_ptr->SetMat4("u_model", transMat);
	glm::mat4 view = camera_ptr->GetViewMatrix();
	shader_ptr->SetMat4("u_view", view);
	glm::mat4 projMat = camera_ptr->GetProjectionMatrix();
	shader_ptr->SetMat4("u_proj", projMat);


	glBindVertexArray(mesh.GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawElements(GL_TRIANGLES, mesh.GetVertices().size(), GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Renderer::Render(GameObject& go) {

	Mesh& mesh = go.GetMesh();
	if (&mesh == nullptr) return;

	Texture& texture = go.GetTexture();
	if (&texture == nullptr) std::cout << "no texture";

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader_ptr->Use();

	glm::mat4 transMat = go.GetTransform().GetMatrix();
	shader_ptr->SetMat4("u_model", transMat);
	glm::mat4 view = camera_ptr->GetViewMatrix();
	shader_ptr->SetMat4("u_view", view);
	glm::mat4 projMat = camera_ptr->GetProjectionMatrix();
	shader_ptr->SetMat4("u_proj", projMat);

	shader_ptr->SetInt("u_texture", 0);
	texture.Bind();

	glBindVertexArray(mesh.GetVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, mesh.GetVertices().size(), GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);	
}

void Renderer::Render(std::vector<GameObject>& gos) {
	for (GameObject& go : gos) Render(go);
}

void Renderer::Render(Scene& scene) {
	Render(scene.GetGameObjects());
}



void Renderer::SetShader(ShaderProgram& shader) {
	shader_ptr = &shader;
}

void Renderer::SetCamera(Camera& camera) {
	camera_ptr = &camera;
}


