#pragma once

#include "missan.hpp"

using namespace Missan;

// a script implementing a flying fps style camera
class FPSCamera : public Component {

public:

    // How fast the camera moves
    float moveSpeed = 5.0f;

    // How fast the camera rotates, or mouse sensitivity if you will
    float rotationSpeedDeg = 30.0f;

    // limits maximum pitch (in degrees), i.e. rotation on the x-axis. Recommended not higher than 89.9
    float pitchConstraint = 89.9f;

    // Controls wheter this script is active. 
    // this is handled by another script (Menu)
    bool* moveCam;



    void Update() {
        if (!*moveCam) return;

        // change rotation based on mouse input
        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::unscaledDeltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::unscaledDeltaTime;
        Transform& transform = *GetGameObject().GetComponent<Transform>();
        
        transform.rotationDeg.y += dyRot;
        transform.rotationDeg.x = glm::clamp(transform.rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);

        // using axes like this is more predictable, since holding down
        // e.g. W and S at the same time will not move camera
        int xAxis = 0, zAxis = 0;
        if (Input::IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
        if (Input::IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
        if (Input::IsKeyPressed(GLFW_KEY_S)) zAxis += 1;
        if (Input::IsKeyPressed(GLFW_KEY_W)) zAxis -= 1;

        // remember to use deltatime for smooth movement
        float dx = (float)xAxis * moveSpeed * Time::unscaledDeltaTime;
        float dz = (float)zAxis * moveSpeed * Time::unscaledDeltaTime;

        // move camera relative to its rotation
        transform.position += dx * transform.GetRightVector();
        transform.position += dz * transform.GetBackwardVector();
    }



    // currently all Components, and thus all scripts, require and implementation of this method
    FPSCamera* Clone() const { return new FPSCamera(*this); }   // necessary for deep-cloning

};