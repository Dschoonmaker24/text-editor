#include "Renderer.hpp"

#include <Application.hpp>

#include "Framebuffer.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
	SDL_Surface* MainWindowSurface;
	Framebuffer* MainFramebuffer;

	int2 ViewportSize;

	void initialize() {
		MainWindowSurface = SDL_GetWindowSurface(Application::MainWindow);

		SDL_GetWindowSizeInPixels(
			Application::MainWindow,
			&ViewportSize.x, &ViewportSize.y
		);

		MainFramebuffer = new Framebuffer(ViewportSize);
	}

	void shutdown() {
		delete MainFramebuffer;
	}

	void handleResizes();

	void render() {
		handleResizes();

		color8 clearColor = { 128, 0, 0 };

		clearFramebuffer(MainFramebuffer, clearColor);

		copyFramebufferToSurface(MainFramebuffer, MainWindowSurface);

		SDL_UpdateWindowSurface(Application::MainWindow);
	}
	
	void handleResizes() {
		int2 newViewportSize;

		SDL_GetWindowSizeInPixels(
			Application::MainWindow,
			&newViewportSize.x, &newViewportSize.y
		);

		if (ViewportSize == newViewportSize) {
			return;
		}

		ViewportSize = newViewportSize;

		MainWindowSurface = SDL_GetWindowSurface(Application::MainWindow);

		delete MainFramebuffer;
		MainFramebuffer = new Framebuffer(ViewportSize);
	}
}