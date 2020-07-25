#include "renderer.hpp"

#include "graphics.hpp"

#include <iostream>

using namespace missan;

// PUBLIC
Renderer::Renderer(Camera& camera) {
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


void Renderer::Render(GameObject& go) {

	Mesh& mesh = go.GetMesh();
	if (&mesh == nullptr) return;

	Texture& texture = go.GetTexture();
	if (&texture == nullptr) std::cout << "no texture";

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	ShaderProgram& shader = Graphics::GetStandardShader();

	shader.Use();

	

	glm::mat4 transMat = go.GetTransform().GetMatrix();
	shader.SetMat4("u_model", transMat);
	glm::mat4 view = camera_ptr->GetViewMatrix();
	shader.SetMat4("u_view", view);
	glm::mat4 projMat = camera_ptr->GetProjectionMatrix();
	shader.SetMat4("u_proj", projMat);

	shader.SetInt("u_texture", 0);
	texture.Bind();

	glBindVertexArray(mesh.vaoID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawElements(GL_TRIANGLES, mesh.vertices.size(), GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);	
}

void Renderer::Render(const std::vector<GameObject*>& gos) {
	for (GameObject* go : gos) Render(*go);
}

void Renderer::Render(Scene& scene) {
	Render(scene.gameObjects);
}




void Renderer::SetCamera(Camera& camera) {
	camera_ptr = &camera;
}


