#pragma once

#include "Framebuffer.hpp"
#include "Bitmap.hpp"

namespace Renderer {
	void drawRect(
		int2 rectMin, int2 rectMax, color8alpha color,
		const Framebuffer* const framebuffer
	);

	void drawBitmap(
		const Bitmap* const bitmap,
		int2 origin,
		const Framebuffer* const framebuffer
	);
}