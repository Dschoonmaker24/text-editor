#include "Application.hpp"

#include <SDL3/SDL.h>

namespace Application {
	bool ApplicationRunning;
	SDL_Window* MainWindow;

	void initialize() {
		SDL_Init(SDL_INIT_VIDEO);

		MainWindow = SDL_CreateWindow(
			"Text Editor",
			800, 600,
			SDL_WINDOW_RESIZABLE
		);
	}

	void shutdown() {
		SDL_DestroyWindow(MainWindow);

		SDL_Quit();
	}

	void mainLoop();

	void run() {
		ApplicationRunning = true;

		while (ApplicationRunning) {
			mainLoop();
		}
	}

	void mainLoop() {
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0) {
			switch (event.type) {
			case SDL_EVENT_QUIT:
				ApplicationRunning = false;
				break;
			}
		}
	}
}