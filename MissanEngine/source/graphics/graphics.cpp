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


void GraphicsInitialize() {
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Shader::unlit = new Shader("resources/shaders/unlit/vertex.shader", "resources/shaders/unlit/fragment.shader");
	Shader::phong = new Shader("resources/shaders/phong/vertex.shader", "resources/shaders/phong/fragment.shader");
	
}

void GraphicsUpdate() {
	Camera* camera = Component<Camera>::instances[0];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec4 clearColor = camera->clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);


	for (auto renderer : Component<Renderer>::instances) {

		Mesh* mesh = renderer->mesh;
		if (!mesh) continue;

		Transform* transform = renderer->gameObject->GetComponent<Transform>();
		Transform* cameraTransform = camera->gameObject->GetComponent<Transform>();
		Material* material = renderer->material;

		Shader* shader = material->shader;
		if (!shader) shader = Shader::unlit;

		Texture* texture = material->texture;
		Light* light = Component<Light>::instances[0];
		

		glUseProgram(shader->programId);
		shader->SetMat4("model", transform->matrix);
		shader->SetMat4("view", cameraTransform->inverseMatrix);
		shader->SetMat4("projection", camera->projectionMatrix);

		glBindVertexArray(mesh->vaoId);
		glEnableVertexAttribArray(0);
		if (texture) {
			glEnableVertexAttribArray(1);
			shader->SetInt("textureSlot", 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->id);
		}
		glEnableVertexAttribArray(2);


		if (shader == Shader::unlit) {
			
			shader->SetVec4("materialColor", material->ambient);

		}
		else if (shader == Shader::phong) {

			shader->SetMat3("normalMatrix", mat3(inverse(transpose(transform->matrix))));
			shader->SetVec3("cameraPosition", cameraTransform->position);

			shader->SetVec3("light.position", light->gameObject->GetComponent<Transform>()->position);
			shader->SetVec4("light.ambient", light->ambient);
			shader->SetVec4("light.diffuse", light->diffuse);
			shader->SetVec4("light.specular", light->specular);			
			
			shader->SetVec4("material.ambient", material->ambient);
			shader->SetVec4("material.diffuse", material->diffuse);
			shader->SetVec4("material.specular", material->specular);
			shader->SetFloat("material.shininess", material->shininess);		
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, mesh->elementCount, GL_UNSIGNED_INT, 0);


		glDisableVertexAttribArray(0);
		if (texture) {
			glBindTexture(GL_TEXTURE_2D, 0);
			glDisableVertexAttribArray(1);
		}
		glDisableVertexAttribArray(2);

	}
}
