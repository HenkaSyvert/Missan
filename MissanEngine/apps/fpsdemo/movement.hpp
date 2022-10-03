#pragma once

#include "missan.hpp"

#include "menu.hpp"
#include "globals.hpp"


using namespace Missan;
using namespace std;
using namespace glm;

// script for making player move like in a generic FPS game,
// and also simulate some physics and collision avoidance
class Movement : public Component {

public:

    
    float moveSpeed = 5.0f;         // How fast the player moves
    float headHeight = 1.2f;        // distance above floor we want the player's eyes to be.     
    float radius = 0.7f;            // to simulate collision avoidance in script, we make player into a sphere
    

    float jumpForce = 120.0f;   
    float timeStamp = 0;
    float jumpDelay = 0.5f;
    bool isGrounded = true;         // does player touch the ground?
    bool canJump = true;


    Transform* transform = nullptr;
    RigidBody* rb = nullptr;


    // makes player stay within map size
    void KeepWithinMap() {
        transform->position.x = clamp(transform->position.x, -cellWidth / 2 + radius, (mapWidth - 0.5f) * cellWidth - radius);
        transform->position.z = clamp(transform->position.z, -cellBreadth / 2 + radius, (mapBreadth - 0.5f) * cellBreadth - radius);
    }

    void CheckJump() {

        // if player is falling through the air, check to see if he hits floor. 
        // if he hits floor, make him stop falling. 
        if (!isGrounded) {         
            if (transform->position.y < headHeight) {       
                cout << "hej";
                isGrounded = true;
                transform->position.y = headHeight;
                rb->forces = { 0,0,0 };
                rb->linearVelocity.y = 0;
                rb->isAffectedByGravity = false;
            }
        }

        // just check if enough time has passed between jumps. 
        if (!canJump) {
            if (Time::time - timeStamp > jumpDelay) {
                canJump = true;
            }
        }

        
        // check if player made a jump, then send him flying straight upwards with an impulse. 
        if (canJump && isGrounded && Input::GetKeyDown(Keycode::Space)) {
            rb->AddImpulse({ 0, jumpForce / rb->mass, 0 });
            rb->AddForce(Physics::gravity / rb->mass);
            isGrounded = false;
            canJump = false;
            timeStamp = Time::time;
        }
        

    }


    void Start() {
        
        transform = gameObject->GetComponent<Transform>();
        rb = gameObject->GetComponent<RigidBody>();

        transform->position.y = headHeight;
        rb->isAffectedByGravity = false;
        rb->mass = 5.0f;
        timeStamp = Time::time;
        

    }

	void Update() {
        if (isPaused) return;

        // using axes like this is more predictable, since holding down
        // e.g. W and S at the same time will make player stand still
        int xAxis = 0, zAxis = 0;
        if (Input::GetKey(Keycode::D)) xAxis += 1;
        if (Input::GetKey(Keycode::A)) xAxis -= 1;
        if (Input::GetKey(Keycode::S)) zAxis -= 1;
        if (Input::GetKey(Keycode::W)) zAxis += 1;

        // use deltatime for smooth, framerate independent movement
        float dx = (float)xAxis * moveSpeed * Time::deltaTime;
        float dz = (float)zAxis * moveSpeed * Time::deltaTime;

        // move camera relative to its rotation
        transform->position += dx * transform->right;
        transform->position += dz * normalize(transform->forward - proj(transform->forward, vec3(0, 1, 0)));
      
        CheckJump();      
        KeepWithinMap();
        

	}



};
