#include "renderer.h"

#include <iostream>

using namespace missan;

// PUBLIC
void Renderer::Prepare() {
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//glFrontFace(GL_CCW);
	glClearColor(0, 0, 1, 1);
}

void Renderer::Render(GameObject& go) {
	Mesh& mesh = go.GetMesh();
	Texture& texture = go.GetTexture();
	if (&texture == nullptr)std::cout << "hej";

	shader_ptr->Use();

	glm::mat4 model = go.GetTransform().GetMatrix();
	shader_ptr->SetUniformMat4("u_model", model);
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


void Renderer::SetShader(ShaderProgram& shader) {
	shader_ptr = &shader;
}

void Renderer::SetCamera(Camera& camera) {
	camera_ptr = &camera;
}


