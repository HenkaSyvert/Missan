#include "renderer.h"

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
	//glFrontFace(GL_CCW);
	glClearColor(0, 0, 1, 1);
}

void Renderer::Render(GameObject& go) {
	Model& model = go.GetModel();
	Mesh& mesh = model.GetMesh();
	Texture& texture = model.GetTexture();
	if (&texture == nullptr)std::cout << "hej";

	shader_ptr->Use();

	glm::mat4 transMat = go.GetTransform().GetMatrix();
	shader_ptr->SetUniformMat4("u_model", transMat);
	glm::mat4 view = camera_ptr->GetViewMatrix();
	shader_ptr->SetUniformMat4("u_view", view);
	glm::mat4 projMat = camera_ptr->GetProjectionMatrix();
	shader_ptr->SetUniformMat4("u_proj", projMat);

	shader_ptr->SetUniform1i("u_texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.GetID());




	glBindVertexArray(mesh.GetVaoID());
	glEnableVertexAttribArray(0);	
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, mesh.GetVertexCount(), GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);	
	shader_ptr->Stop();
}

void Renderer::Render(std::vector<GameObject>& gos) {
	for (GameObject& go : gos)
		Render(go);
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


