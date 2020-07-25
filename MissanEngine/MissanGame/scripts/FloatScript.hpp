#pragma once

#include "missan.hpp"

using namespace missan;

class FloatScript : public Component {

private:
    float yOriginal;
    float amp = 1.0f;
    float freq = 5.0f;

public:
    FloatScript* Clone() const { return new FloatScript(*this); }   // necessary for deep-cloning



    void Start() {
        yOriginal = GetGameObject().GetTransform().position.y;
    }

    void Update() {
        Transform& trans = GetGameObject().GetTransform();
        trans.position.y = yOriginal + amp * sinf(freq * Time::time);
    }

};