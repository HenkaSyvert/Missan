#pragma once

#include "missanpch.hpp"
#include "application.hpp"

using namespace Missan;

// To be defined in client
extern Application* CreateApplication();

// This is the entry point for the Application
int main(int argc, char* argv[]) {

	// TODO:
	// 1. logging
	// 2. benchmarking

	Application* application = CreateApplication();

	application->Run();

	return EXIT_SUCCESS;
}
