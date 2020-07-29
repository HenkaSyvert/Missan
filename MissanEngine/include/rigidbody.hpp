#pragma once

#include "missanpch.hpp"
#include "components/component.hpp"
#include "components/transform.hpp"
#include "components/collider.hpp"
#include "core/time.hpp"

namespace missan {

	class RigidBody : public Component {

	public:


		// The mass of this rigidbody, in kilograms
		float mass = 1.0f;

		// The forces acting on this RigidBody
		glm::vec3 forces = { 0,0,0 };

		// The velocity of this RigidBody
		glm::vec3 velocity = { 0,0,0 };

		void Start() {
			if (GetGameObject().GetComponent<Collider>() == nullptr)
				std::cout << "RigidBody requires Collider Component!\n";
		}
		

		void Update() {

			


		}

		// NOT PART OF PUBLIC API ////////////////////////
		RigidBody* Clone() const { return new RigidBody(*this); }
	};
}