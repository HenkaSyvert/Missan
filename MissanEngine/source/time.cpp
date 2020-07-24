#include "time.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

