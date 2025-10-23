#include "Renderer.hpp"

#include <Application.hpp>

#include "DrawFunctions.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
	SDL_Surface* MainWindowSurface;
	Framebuffer* MainFramebuffer;

	int2 ViewportSize;

	Bitmap* TestBitmap;

	Bitmap* createTestBitmap() {
		Bitmap* bitmap = new Bitmap({100, 100});
		
		int2 coord;
		for (coord.y = 0; coord.y < bitmap->size.y; coord.y++) {
			color8alpha* row = bitmap->data + (bitmap->size.x * coord.y);

			for (coord.x = 0; coord.x < bitmap->size.x; coord.x++) {
				color8alpha color = {
					0, 0, 0, 255
				};

				color.r = coord.x * 255 / bitmap->size.x;
				color.g = coord.y * 255 / bitmap->size.y;

				int2 circlePos = coord;
				circlePos.x = circlePos.x * 2 - bitmap->size.x;
				circlePos.y = circlePos.y * 2 - bitmap->size.y;

				int l = circlePos.x*circlePos.x + circlePos.y*circlePos.y;

				color.a = l < bitmap->size.x*bitmap->size.x ? 255 : 0;
				
				row[coord.x] = color;
			}
		}


		return bitmap;
	}

	void initialize() {
		MainWindowSurface = SDL_GetWindowSurface(Application::MainWindow);

		SDL_GetWindowSizeInPixels(
			Application::MainWindow,
			&ViewportSize.x, &ViewportSize.y
		);

		MainFramebuffer = new Framebuffer(ViewportSize);

		TestBitmap = createTestBitmap();
	}

	void shutdown() {
		delete TestBitmap;

		delete MainFramebuffer;
	}

	void handleResizes();

	void render() {
		handleResizes();

		color8 clearColor = { 128, 0, 0 };

		clearFramebuffer(MainFramebuffer, clearColor);

		drawRect({100, 100}, {200, 200}, {0, 0, 128, 255}, MainFramebuffer);
		drawBitmap(TestBitmap, { 400, 100 }, MainFramebuffer);

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