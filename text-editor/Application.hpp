#pragma once

struct SDL_Window;

namespace Application {
	inline bool ApplicationRunning;
	inline bool NeedsRender;
	inline SDL_Window* MainWindow;

	void initialize();
	void shutdown();

	void run();
}