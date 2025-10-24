#include "Application.hpp"

#include "Renderer/Renderer.hpp"
#include "FontLoader.hpp"

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

		FontLoader::initialize();

		MainFontData = new FontLoader::FontData();

		FontLoader::loadFontDataFromFile("arial.ttf", MainFontData);
		FontLoader::generateFontFromFontData(MainFontData, 256, MainFont);
		Renderer::MainFont = &MainFont;
	}

	void shutdown() {
		delete MainFontData;
		FontLoader::shutdown();

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
			case SDL_EVENT_WINDOW_RESIZED:
				NeedsRender = true;
			}
		}

		if (NeedsRender) {
			Renderer::render();
			NeedsRender = false;
		}
	}
}