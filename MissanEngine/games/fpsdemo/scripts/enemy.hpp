#pragma once

#include "missan.hpp"
#include "entitycomponentsystem.hpp"

using namespace Missan;

class Enemy : public Component {


	Transform* playerTransform;
	float minDistance = 2;
	Transform* transform;
	float speed = 2;

	void Start() {

		transform = gameObject->GetComponent<Transform>();

		auto gameObjects = EcsGetGameObjects();
		for (auto& g : gameObjects) {
			if (g->tag == "player") {
				playerTransform = g->GetComponent<Transform>();
				break;
			}
		}

	}

	void Update() {

		glm::vec3 displacement = playerTransform->position - transform->position;
		float distance = glm::length(displacement);
		if (distance > minDistance) {

			glm::vec3 direction = glm::normalize(displacement);

			transform->position += direction * Time::deltaTime * speed;

		}


	}
	Enemy* Clone() const { return new Enemy(*this); }   // necessary for deep-cloning

};