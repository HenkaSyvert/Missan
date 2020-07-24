#pragma once

#include "missan.hpp"

using namespace missan;

class FPSCamera : public Component {

private:
    float moveSpeed = 5.0f;
    float rotationSpeedDeg = 30.0f;
    float pitchConstraint = 89.0f;

public:
    bool* moveCam;

    void Update() override {
        if (!*moveCam) return;


        float dyRot = -Input::mouseDelta.x * rotationSpeedDeg * Time::deltaTime;
        float dxRot = -Input::mouseDelta.y * rotationSpeedDeg * Time::deltaTime;

        Transform& transform = gameObject_ptr->GetTransform();
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