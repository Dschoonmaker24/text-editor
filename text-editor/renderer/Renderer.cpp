#include "Renderer.hpp"

#include <Application.hpp>

#include "Framebuffer.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
	SDL_Surface* MainWindowSurface;
	Framebuffer* MainFramebuffer;

	int ViewportWidth, ViewportHeight;

	void initialize() {
		MainWindowSurface = SDL_GetWindowSurface(Application::MainWindow);

		SDL_GetWindowSizeInPixels(
			Application::MainWindow,
			&ViewportWidth, &ViewportHeight
		);

		MainFramebuffer = new Framebuffer(ViewportWidth, ViewportHeight);
	}

	void shutdown() {
		delete MainFramebuffer;
	}

	void handleResizes();

	void render() {
		handleResizes();

		unsigned char clearColor[3] = { 128u, 0u, 0u };

		clearFramebuffer(MainFramebuffer, clearColor);

		copyFramebufferToSurface(MainFramebuffer, MainWindowSurface);

		SDL_UpdateWindowSurface(Application::MainWindow);
	}
	
	void handleResizes() {
		int newViewportWidth, newViewportHeight;

		SDL_GetWindowSizeInPixels(
			Application::MainWindow,
			&newViewportWidth, &newViewportHeight
		);

		if (
			ViewportWidth == newViewportWidth &&
			ViewportHeight == newViewportHeight
		) {
			return;
		}

		ViewportWidth = newViewportWidth;
		ViewportHeight = newViewportHeight;

		MainWindowSurface = SDL_GetWindowSurface(Application::MainWindow);

		delete MainFramebuffer;
		MainFramebuffer = new Framebuffer(ViewportWidth, ViewportHeight);
	}
}