#pragma once

#include "missan.hpp"

using namespace missan;

class FPSCamera : public Component {

private:
    float moveSpeed = 5.0f;
    float rotationSpeedDeg = 30.0f;
    float pitchConstraint = 89.9f;

public:
    bool* moveCam;

    FPSCamera* Clone() const { return new FPSCamera(*this); }   // necessary for deep-cloning

    void Update() {
        if (!*moveCam) return;


        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::deltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::deltaTime;

        Transform& transform = GetGameObject().GetTransform();
        transform.rotationDeg.y += dyRot;
        transform.rotationDeg.x = glm::clamp(transform.rotationDeg.x + dxRot, -pitchConstraint, pitchConstraint);

        int xAxis = 0, zAxis = 0;
        if (Input::IsKeyPressed(GLFW_KEY_D)) xAxis += 1;
        if (Input::IsKeyPressed(GLFW_KEY_A)) xAxis -= 1;
        if (Input::IsKeyPressed(GLFW_KEY_S)) zAxis += 1;
        if (Input::IsKeyPressed(GLFW_KEY_W)) zAxis -= 1;

        float dx = (float)xAxis * moveSpeed * Time::deltaTime;
        float dz = (float)zAxis * moveSpeed * Time::deltaTime;

        transform.position += dx * transform.GetRightVector();
        transform.position += dz * transform.GetBackwardVector();
    }

};