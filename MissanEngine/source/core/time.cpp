#include "core/time.hpp"

#include "missanpch.hpp"

using namespace missan;

namespace {

	double time_	  = 0.0f;
	double deltaTime_ = 0.0f;

}


// PUBLIC
const double& Time::time      = time_;
const double& Time::deltaTime = deltaTime_;

void Time::Update() {
	double timeStamp = glfwGetTime();
	deltaTime_ = timeStamp - time_;
	time_ = timeStamp;
}

