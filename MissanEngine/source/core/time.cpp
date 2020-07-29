#include "core/time.hpp"

#include "missanpch.hpp"

using namespace missan;

namespace {

	float time_			= 0.0f;
	float unscaledTime_ = 0.0f;
	float deltaTime_    = 0.0f;
	float unscaledDeltaTime_ = 0.0f;

}


// PUBLIC
const float& Time::time = time_;
const float& Time::unscaledTime = unscaledTime_;
const float& Time::deltaTime = deltaTime_;
const float& Time::unscaledDeltaTime = unscaledDeltaTime_;
float Time::timeScale = 1.0f;

void Time::Update() {
	double timeStamp = glfwGetTime();
	unscaledDeltaTime_ = (float)timeStamp - unscaledTime_;
	unscaledTime_ = (float)timeStamp;

	time_ = unscaledTime_ * timeScale;
	deltaTime_ = unscaledDeltaTime_ * timeScale;
}

