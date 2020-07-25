#pragma once

#include "missan.hpp"

#include <iostream> //debug

using namespace missan;

class FloatScript : public Component {

private:
    float amp = 1.0f;
    float freq = 5.0f;

public:

    FloatScript* Clone() const { return new FloatScript(*this); }   // necessary for deep-cloning

    void Update() {

        Transform& trans = GetGameObject().GetTransform();

        trans.position.y = amp * sinf(freq * Time::time);
    }

};