#pragma once

#include "missan.hpp"

using namespace Missan;

// script for making player move like in a generic FPS game,
// and also simulate some physics and collision avoidance
class Movement : public Component {

public:

    // How fast the player moves
    float moveSpeed = 5.0f;

	void Start() {
        auto& transform = *GetGameObject().GetComponent<Transform>();


        // using axes like this is more predictable, since holding down
        // e.g. W and S at the same time will not move camera
        int xAxis = 0, zAxis = 0;
        if (Input::IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
        if (Input::IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
        if (Input::IsKeyPressed(GLFW_KEY_S)) zAxis -= 1;
        if (Input::IsKeyPressed(GLFW_KEY_W)) zAxis += 1;

        // remember to use deltatime for smooth movement
        float dx = (float)xAxis * moveSpeed * Time::unscaledDeltaTime;
        float dz = (float)zAxis * moveSpeed * Time::unscaledDeltaTime;

        // move camera relative to its rotation
        transform.position += dx * transform.GetRightVector();
        transform.position += dz * glm::normalize(-transform.GetBackwardVector() - glm::vec3(0, 1, 0));

	}


    Movement* Clone() const { return new Movement(*this); }


};
