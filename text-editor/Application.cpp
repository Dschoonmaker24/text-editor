#include "Application.hpp"

#include "Renderer/Renderer.hpp"

#include <SDL3/SDL.h>

namespace Application {
	void initialize() {
		SDL_Init(SDL_INIT_VIDEO);

		MainWindow = SDL_CreateWindow(
			"Text Editor",
			800, 600,
			SDL_WINDOW_RESIZABLE
		);

		Renderer::initialize();
	}

	void shutdown() {
		Renderer::shutdown();

		SDL_DestroyWindow(MainWindow);

		SDL_Quit();
	}

	void mainLoop();

	void run() {
		ApplicationRunning = true;
		NeedsRender = true;

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

		if (NeedsRender) {
			Renderer::render();
		}
	}
}