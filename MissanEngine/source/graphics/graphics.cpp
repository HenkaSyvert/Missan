#include "graphics/light.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "graphics/renderer.hpp"
#include "graphics/camera.hpp"
#include "graphics/texture.hpp"

#include "physics/transform.hpp"
#include "internal.hpp"
#include "ecs/gameobject.hpp"
#include "ecs/component.hpp"

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
	Shader::unlit = new Shader("resources/shaders/unlit.vs", "resources/shaders/unlit.fs");
	Shader::diffuseSpecular = new Shader("resources/shaders/diffuseSpecular.vs", "resources/shaders/diffuseSpecular.fs");
}

void GraphicsUpdate() {
	
	RawArray<Camera> cameras = Component::GetRawArray<Camera>();
	if (cameras.count == 0) return;

	// TODO: add support for several cameras...
	Camera& camera = cameras[0];


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec4 clearColor = camera.clearColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

	RawArray<Renderer> renderers = Component::GetRawArray<Renderer>();

	for (size_t i = 0; i < renderers.count; i++) {

		Renderer& renderer = renderers[i];

		if (!renderer.mesh) {
			continue;
		}

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(renderer.mesh->vaoId);
		glEnableVertexAttribArray(0);

		Shader& shader = *renderer.material->shader;
		glUseProgram(shader.programId);

		if (&shader == Shader::unlit) {
			mat4 transMat = Component::Get<Transform>(renderer.gameObjectId)->matrix;
			shader.SetMat4("u_model", transMat);

			mat4 view = Component::Get<Transform>(camera.gameObjectId)->inverseMatrix;
			shader.SetMat4("u_view", view);
			shader.SetMat4("u_proj", camera.projectionMatrix);

			Texture* texture = renderer.material->texture;
			shader.SetVec4("u_materialColor", renderer.material->ambient);
			if (texture) {
				glEnableVertexAttribArray(1);
				shader.SetInt("u_texture", 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->textureId);
			}

			glDrawElements(GL_TRIANGLES, renderer.mesh->elementCount, GL_UNSIGNED_INT, 0);

			if (texture) {
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisableVertexAttribArray(1);
			}

			glDisableVertexAttribArray(0);

		}
		else if (&shader == Shader::diffuseSpecular) {
			
			shader.SetMat4("model", Component::Get<Transform>(renderer.gameObjectId)->matrix);
			shader.SetMat4("view", Component::Get<Transform>(camera.gameObjectId)->inverseMatrix);
			shader.SetMat4("projection", camera.projectionMatrix);
			shader.SetMat3("normalMatrix", mat3(inverse(transpose(Component::Get<Transform>(renderer.gameObjectId)->matrix))));
			shader.SetVec3("cameraPosition", Component::Get<Transform>(camera.gameObjectId)->position);

			// TODO: add supprt for several lights...
			RawArray<Light> lights = Component::GetRawArray<Light>();
			Light* light = &lights[0];
			if (light) {
				shader.SetVec3("light.position", Component::Get<Transform>(light->gameObjectId)->position);
				shader.SetVec4("light.ambient", light->ambient);
				shader.SetVec4("light.diffuse", light->diffuse);
				shader.SetVec4("light.specular", light->specular);
			}
			else {
				// idk some default values for non-light?
				shader.SetVec3("light.position", {0,0,0});
				shader.SetVec4("light.ambient", {1,1,1,1});
				shader.SetVec4("light.diffuse", {1,1,1,1});
				shader.SetVec4("light.specular", {1,1,1,1});
			}
			Material* material = renderer.material;
			shader.SetVec4("material.ambient", material->ambient);
			shader.SetVec4("material.diffuse", material->diffuse);
			shader.SetVec4("material.specular", material->specular);
			shader.SetFloat("material.shininess", material->shininess);

			Texture* texture = renderer.material->texture;
			if (texture) {
				glEnableVertexAttribArray(1);
				shader.SetInt("textureSlot", 0);
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, texture->id);
				glBindTexture(GL_TEXTURE_2D, 0);
				glDisableVertexAttribArray(1);
			}

			glEnableVertexAttribArray(2);
			glDrawElements(GL_TRIANGLES, renderer.mesh->elementCount, GL_UNSIGNED_INT, 0);
			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(2);

		}
		else {
			cout << "wtf invalid shader\n";
		}

	}
}
