#pragma once

#include "Framebuffer.hpp"
#include "Font.hpp"

namespace Renderer {
	void drawRect(
		int2 rectMin, int2 rectMax, color8alpha color,
		const Framebuffer* const framebuffer
	);

	void drawBitmap(
		const Bitmap* const bitmap,
		color8alpha color,
		int2 origin,
		const Framebuffer* const framebuffer
	);

	void drawText(
		const char* text,
		const Font* const font,
		color8alpha color,
		int2 origin,
		const Framebuffer* const framebuffer
	);
}