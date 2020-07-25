#pragma once

#include "missan.hpp"

using namespace missan;

// Makes GameObject "float" up and down on y-axis
class FloatScript : public Component {

private:
    float yOriginal;
    float amp = 1.0f;
    float freq = 5.0f;

public:
    FloatScript* Clone() const { return new FloatScript(*this); }   // necessary for deep-cloning



    void Start() {
        yOriginal = GetGameObject().GetComponent<Transform>()->position.y;
    }

    void Update() {
        GetGameObject().GetComponent<Transform>()->position.y = yOriginal + amp * sinf(freq * Time::time);

    }

};