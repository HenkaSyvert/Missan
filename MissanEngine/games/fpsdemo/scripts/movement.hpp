#pragma once

#include "missan.hpp"

#include "menu.hpp"
#include "globals.hpp"

using namespace Missan;

// script for making player move like in a generic FPS game,
// and also simulate some physics and collision avoidance
class Movement : public Component {

public:

    // How fast the player moves
    float moveSpeed = 5.0f;

    bool* isPaused;

    Transform* transform;

    // to simulate collision avoidance in script, we make player into a sphere
    float radius = 0.7f;

    std::vector<glm::ivec2> columns;

    // does player touch the ground?
    bool isGrounded = true;

    RigidBody* rb;

    float jumpForce = 120.0f;
    float headHeight = 1.2f;
    
    float timeStamp;
    float jumpDelay = 0.5f;
    bool canJump = true;

    // makes player stay within map size
    void KeepWithinMap() {
        transform->position.x = glm::clamp(transform->position.x, -cellWidth / 2 + radius, (mapWidth - 0.5f) * cellWidth - radius);
        transform->position.z = glm::clamp(transform->position.z, -cellBreadth / 2 + radius, (mapBreadth - 0.5f) * cellBreadth - radius);
    }

    void AvoidColumns() {

        for (auto& c : columns) {
            bool collision = false;
            
            float px = transform->position.x;
            float pz = transform->position.z;

            float cx = c.x * cellWidth;
            float cz = c.y * cellBreadth;

            
            bool xOverlap = (px - radius < cx + cellWidth   / 2) && (px + radius > cx - cellWidth   / 2);
            bool zOverlap = (pz - radius < cz + cellBreadth / 2) && (pz + radius > cz - cellBreadth / 2);
            collision = xOverlap && zOverlap;

            float xDisplacement = (px > cx) ? (cx + cellWidth / 2) - (px - radius) : (cx - cellWidth / 2) - (px + radius);
            float zDisplacement = (pz > cz) ? (cz + cellBreadth / 2) - (pz - radius) : (cz - cellBreadth / 2) - (pz + radius);


            if (collision) {
                if (abs(xDisplacement) < abs(zDisplacement)) {
                    transform->position.x += xDisplacement;
                }
                else {
                    transform->position.z += zDisplacement;
                }
            }

        }

    }


    void CheckJump() {

        if (!isGrounded) {
            if (transform->position.y < headHeight) {
                isGrounded = true;
                transform->position.y = headHeight;
                rb->forces = { 0,0,0 };
                rb->linearVelocity.y = 0;
            }
        }

        if (!canJump) {
            if (Time::time - timeStamp > jumpDelay) {
                canJump = true;
            }
        }

        if (canJump && isGrounded && Input::IsKeyPressed(GLFW_KEY_SPACE)) {
            rb->AddImpulse({ 0, jumpForce / rb->mass, 0 });
            rb->AddForce(Physics::gravity / rb->mass);
            isGrounded = false;
            canJump = false;
            timeStamp = Time::time;
        }

    }


    void Start() {
        isPaused = &GetGameObject().GetComponent<Menu>()->isPaused;
        transform = GetGameObject().GetComponent<Transform>();
        
        rb = GetGameObject().GetComponent<RigidBody>();
        transform->position.y = headHeight;
        rb->isAffectedByGravity = false;
        rb->mass = 5.0f;
        timeStamp = Time::time;

    }

	void Update() {

        if (*isPaused) return;

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
        transform->position += dx * transform->GetRightVector();
        transform->position += dz * glm::normalize(-transform->GetBackwardVector() - glm::proj(-transform->GetBackwardVector(), glm::vec3(0, 1, 0)));

        
        CheckJump();
        

        KeepWithinMap();
        AvoidColumns();

	}


    Movement* Clone() const { return new Movement(*this); }


};
