#include "pch.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "renderer.hpp"
#include "camera.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "internal.hpp"
#include "ecs.hpp"
#include "engine.hpp"

using namespace Missan;
using namespace std;
using namespace glm;


const Color Color::red		 = { 1.0f, 0.0f, 0.0f, 1.0f };
const Color Color::green	 = { 0.0f, 1.0f, 0.0f, 1.0f };
const Color Color::blue		 = { 0.0f, 0.0f, 1.0f, 1.0f };
const Color Color::white	 = { 1.0f, 1.0f, 1.0f, 1.0f };
const Color Color::black	 = { 0.0f, 0.0f, 0.0f, 1.0f };
const Color Color::clear	 = { 0.0f, 0.0f, 0.0f, 0.0f };
const Color Color::cyan		 = { 0.0f, 1.0f, 1.0f, 1.0f };
const Color Color::magenta	 = { 1.0f, 0.0f, 1.0f, 1.0f };
const Color Color::yellow	 = { 1.0f, 1.0f, 0.0f, 1.0f };
const Color Color::grey		 = { 0.5f, 0.5f, 0.5f, 1.0f };
const Color Color::darkGrey  = { 0.2f, 0.2f, 0.2f, 1.0f };
const Color Color::lightGrey = { 0.8f, 0.8f, 0.8f, 1.0f };

Material* Material::defaultMaterial = nullptr;

const string dataFolder = "../MissanEngine/data/";

void GraphicsInitialize() {
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	Shader::unlit = new Shader(dataFolder + "shaders/unlit.glsl");
	Shader::phong = new Shader(dataFolder + "shaders/phong.glsl");

	Material::defaultMaterial = new Material();
	Material::defaultMaterial->shader = Shader::phong;
	Material::defaultMaterial->texture = Resources::GetTexture(dataFolder + "textures/blank.png");

}

void GraphicsUpdate() {
	Camera* camera = Camera::instances[0];

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vec4 clearColor = camera->backgroundColor;
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);


	for (auto renderer : Renderer::instances) {

		if (!renderer->isEnabled) continue;

		Mesh* mesh = renderer->mesh;
		if (!mesh) continue;

		Material* material = renderer->material;
		Shader* shader = material->shader;
		Texture* texture = material->texture;

		Light* light = Light::instances[0];
		
		glUseProgram(shader->programId);
		shader->SetMat4("model", renderer->transform->localToWorldMatrix);
		shader->SetMat4("view", camera->transform->worldToLocalMatrix);
		shader->SetMat4("projection", camera->projectionMatrix);

		glBindVertexArray(mesh->vaoId);
		glEnableVertexAttribArray(0);

		glEnableVertexAttribArray(1);
		shader->SetInt("textureSlot", 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->id);
		
		glEnableVertexAttribArray(2);


		if (shader == Shader::unlit) {
			
			shader->SetVec4("materialColor", material->ambient);

		}
		else if (shader == Shader::phong) {

			shader->SetMat3("normalMatrix", mat3(inverse(transpose(renderer->transform->localToWorldMatrix))));
			shader->SetVec3("cameraPosition", camera->transform->position);

			shader->SetVec3("light.position", light->transform->position);
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
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

	}

}
