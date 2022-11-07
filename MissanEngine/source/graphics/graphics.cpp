#include "graphics/light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/renderer.hpp"
#include "graphics/camera.hpp"
#include "graphics/texture.hpp"

#include "physics/transform.hpp"
#include "internal.hpp"
#include "component.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

using namespace Missan;
using namespace std;
using namespace glm;

Mesh::Mesh(int vaoId, int elementCount) {
	this->vaoId = vaoId;
	this->elementCount = elementCount;
}

void GraphicsInitialize() {
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Shader::unlit = new Shader("resources/shaders/unlit/vertex.shader", "resources/shaders/unlit/fragment.shader");
	Shader::phong = new Shader("resources/shaders/phong/vertex.shader", "resources/shaders/phong/fragment.shader");
	
}

void GraphicsUpdate() {
	auto f = Component<Camera>::instances;
	Camera* camera = Component<Camera>::instances[0];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec4 clearColor = camera->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);


	for (auto renderer : Component<Renderer>::instances) {

		if (!renderer->mesh) continue;

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(renderer->mesh->vaoId);
		glEnableVertexAttribArray(0);

		Shader* shader = renderer->material->shader;
		if (!shader) shader = Shader::unlit;

		glUseProgram(shader->programId);

		if (shader == Shader::unlit) {

			mat4 transMat = renderer->gameObject->GetComponent<Transform>()->matrix;
			shader->SetMat4("u_model", transMat);

			mat4 view = camera->gameObject->GetComponent<Transform>()->inverseMatrix;
			shader->SetMat4("u_view", view);
			shader->SetMat4("u_proj", camera->projectionMatrix);

			Texture* texture = renderer->material->texture;
			shader->SetVec4("u_materialColor", renderer->material->ambient);
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
		else if (shader == Shader::phong) {

			shader->SetMat4("model", renderer->gameObject->GetComponent<Transform>()->matrix);
			shader->SetMat4("view", camera->gameObject->GetComponent<Transform>()->inverseMatrix);
			shader->SetMat4("projection", camera->projectionMatrix);
			shader->SetMat3("normalMatrix", mat3(inverse(transpose(renderer->gameObject->GetComponent<Transform>()->matrix))));
			shader->SetVec3("cameraPosition", camera->gameObject->GetComponent<Transform>()->position);

			Light* light = Component<Light>::instances[0];
			if (light) {
				shader->SetVec3("light.position", light->gameObject->GetComponent<Transform>()->position);
				shader->SetVec4("light.ambient", light->ambient);
				shader->SetVec4("light.diffuse", light->diffuse);
				shader->SetVec4("light.specular", light->specular);
			}
			Material* material = renderer->material;
			shader->SetVec4("material.ambient", material->ambient);
			shader->SetVec4("material.diffuse", material->diffuse);
			shader->SetVec4("material.specular", material->specular);
			shader->SetFloat("material.shininess", material->shininess);

			Texture* texture = renderer->material->texture;
			if (texture) {
				glEnableVertexAttribArray(1);
				shader->SetInt("textureSlot", 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->id);
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisableVertexAttribArray(1);
			}

			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, renderer->mesh->elementCount, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(2);

		}

	}
}
