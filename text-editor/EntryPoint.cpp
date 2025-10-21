#include <iostream>

#include "Application.hpp"


#include <SDL3/SDL_main.h>

int main(int argc, char** argv) {
	Application::initialize();

	Application::run();

	Application::shutdown();

	return 0;
}