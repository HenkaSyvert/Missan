#pragma once

#include "missan.hpp"

using namespace Missan;

// Makes GameObject "float" up and down on y-axis
class FloatScript : public Component {

private:

    // save the original y value
    float yOriginal;

public:

    // Amplitude of the sinus float
    float amp = 1.0f;

    // frequency of the sinus float
    float freq = 5.0f;
    
    void Start() {
        yOriginal = GetGameObject().GetComponent<Transform>()->position.y;
    }

    void Update() {
        GetGameObject().GetComponent<Transform>()->position.y = yOriginal + amp * sinf(freq * Time::time);
    }

    // currently all Components, and thus all scripts, require and implementation of this method
    FloatScript* Clone() const { return new FloatScript(*this); }

};