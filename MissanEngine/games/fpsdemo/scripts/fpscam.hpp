#pragma once

#include "missan.hpp"

using namespace Missan;

// script for moving camera with mouse on y axis, and x axis (constrained to 89.9 degrees)
class FPSCamera : public Component {

public:

    // How fast the camera rotates, or mouse sensitivity if you will
    float rotationSpeedDeg = 30.0f;

    // limits maximum pitch (in degrees), i.e. rotation on the x-axis. Recommended not higher than 89.9
    float pitchConstraint = 89.9f;

    // Controls wheter this script is active. 
    bool* moveCam;




    void Update() {
        if (!*moveCam) return;

        // change rotation based on mouse input
        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::unscaledDeltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::unscaledDeltaTime;
        Transform& transform = *GetGameObject().GetComponent<Transform>();
        
        transform.rotationDeg.y += dyRot;
        transform.rotationDeg.x = glm::clamp(transform.rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);

        
    }



    // currently all Components, and thus all scripts, require and implementation of this method
    FPSCamera* Clone() const { return new FPSCamera(*this); }   // necessary for deep-cloning

};