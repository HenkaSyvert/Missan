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
#include <iostream>

using namespace Missan;
using namespace std;
using namespace glm;


#define MISSAN_DEBUG_GRAPHICS 0

void GraphicsInitialize() {
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void GraphicsUpdate() {
	
	RawArray<Camera> cameras = Component::GetRawArray<Camera>();
	for(size_t j = 0; j < cameras.count; j++){
		Camera& camera = cameras[0];

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vec4 clearColor = camera.clearColor;
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

		RawArray<Renderer> renderers = Component::GetRawArray<Renderer>();
		for (size_t i = 0; i < renderers.count; i++) {
			Renderer& renderer = renderers[i];

			Mesh* mesh = ECS::Get<Mesh>(renderer.meshId);
			if (!mesh) {
				if (MISSAN_DEBUG_GRAPHICS)cout << "\tmesh = null, skipping..\n";
				continue;
			}

			Material* material = ECS::Get<Material>(renderer.materialId);
			Shader* shader = nullptr;
			Texture* texture = nullptr;
			if (material) {
				shader = ECS::Get<Shader>(material->shaderId);
				texture = ECS::Get<Texture>(material->textureId);
				if (MISSAN_DEBUG_GRAPHICS) {
					if (!shader)cout << "\tshader = null\n";
					if (!texture)cout << "\ttexture = null\n";
				}
			}
			else {
				if (MISSAN_DEBUG_GRAPHICS)cout << "\tmaterial = null\n";
			}

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glBindVertexArray(mesh->vaoId);
			glEnableVertexAttribArray(0);

			//temp
			if (!shader) shader = &ECS::AsRawArray<Shader>()[0];

			glUseProgram(shader->programId);

			if (true) {
				mat4 transMat = Component::Get<Transform>(renderer.gameObjectId)->matrix;
				shader->SetMat4("u_model", transMat);

				mat4 view = Component::Get<Transform>(camera.gameObjectId)->inverseMatrix;
				shader->SetMat4("u_view", view);
				shader->SetMat4("u_proj", camera.projectionMatrix);

				shader->SetVec4("u_materialColor", material->ambient);
				if (texture) {
					glEnableVertexAttribArray(1);
					shader->SetInt("u_texture", 0);
					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, texture->textureId);
				}

				glDrawElements(GL_TRIANGLES, mesh->elementCount, GL_UNSIGNED_INT, 0);

				if (texture) {
					glBindTexture(GL_TEXTURE_2D, 0);
					glDisableVertexAttribArray(1);
				}

				glDisableVertexAttribArray(0);

			}
			/*
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
					shader.SetVec3("light.position", { 0,0,0 });
					shader.SetVec4("light.ambient", { 1,1,1,1 });
					shader.SetVec4("light.diffuse", { 1,1,1,1 });
					shader.SetVec4("light.specular", { 1,1,1,1 });
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

			}*/
		}
	}
}
