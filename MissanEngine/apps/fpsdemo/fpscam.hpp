#pragma once

#include "missan.hpp"

#include "menu.hpp"
#include "globals.hpp"

using namespace Missan;
using namespace glm;

// script for moving camera with mouse on y axis, and x axis (constrained to 89.9 degrees)
class FPSCamera : public Component {

public:

    // How fast the camera rotates, or mouse sensitivity
    float rotationSpeedDeg = 30.0f;

    // limits maximum pitch (in degrees), i.e. rotation on the x-axis. Recommended not higher than 89.9
    float pitchConstraint = 89.9f;


    Transform* transform = nullptr;

    void Start() {
        // fetching this pointer once here is cheaper than doing it in every frame in Update(). 
        transform = gameObject->GetComponent<Transform>();
    }

    void Update() {
        if (isPaused) return;

        // change rotation based on mouse input
        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::deltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::deltaTime;
  
        transform->rotation.y += dyRot;
        transform->rotation.x = clamp(transform->rotation.x + dxRot, -pitchConstraint, pitchConstraint);

        
    }


};