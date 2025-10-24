#pragma once

#include "Font.hpp"

namespace Renderer {
	inline Font* MainFont;

	void initialize();
	void shutdown();

	void render();
}