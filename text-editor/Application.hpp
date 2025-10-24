#pragma once

struct SDL_Window;

#include "FontLoader.hpp"

namespace Application {
	inline bool ApplicationRunning;
	inline bool NeedsRender;
	inline SDL_Window* MainWindow;

	inline FontLoader::FontData* MainFontData;
	inline Renderer::Font MainFont;

	void initialize();
	void shutdown();

	void run();
}