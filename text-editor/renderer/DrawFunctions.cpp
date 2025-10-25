#include "DrawFunctions.hpp"

namespace Renderer {
	void clipRect(int2& rectMin, int2& rectMax, int2 boundsMin, int2 boundsMax) {
		rectMin.x = rectMin.x < boundsMin.x ? boundsMin.x : rectMin.x;
		rectMin.x = rectMin.x > boundsMax.x ? boundsMax.x : rectMin.x;

		rectMin.y = rectMin.y < boundsMin.y ? boundsMin.y : rectMin.y;
		rectMin.y = rectMin.y > boundsMax.y ? boundsMax.y : rectMin.y;

		rectMax.x = rectMax.x < boundsMin.x ? boundsMin.x : rectMax.x;
		rectMax.x = rectMax.x > boundsMax.x ? boundsMax.x : rectMax.x;

		rectMax.y = rectMax.y < boundsMin.y ? boundsMin.y : rectMax.y;
		rectMax.y = rectMax.y > boundsMax.y ? boundsMax.y : rectMax.y;
	}

	void drawRect(
		int2 rectMin, int2 rectMax, color8alpha color,
		const Framebuffer* const framebuffer
	) {
		color8 srcColor = { color.r, color.g, color.b };
		uint8 blendFactor = color.a;

		clipRect(rectMin, rectMax, { 0, 0 }, framebuffer->size);

		int2 pixelCoord;

		for (pixelCoord.y = rectMin.y; pixelCoord.y < rectMax.y; pixelCoord.y++) {
			color8* framebufferRow = framebuffer->data + (framebuffer->size.x * pixelCoord.y);

			for (pixelCoord.x = rectMin.x; pixelCoord.x < rectMax.x; pixelCoord.x++) {
				color8 dstColor = framebufferRow[pixelCoord.x];

				color8 blendedColor = blendColors(dstColor, srcColor, blendFactor);

				framebufferRow[pixelCoord.x] = blendedColor;
			}
		}
	}

	void drawBitmap(
		const Bitmap* const bitmap,
		color8alpha color,
		int2 origin,
		const Framebuffer* const framebuffer
	) {
		int2 rectMin = origin, rectMax = origin + bitmap->size;

		clipRect(rectMin, rectMax, {0, 0}, framebuffer->size);

		int2 bitmapRelativeRectMin = rectMin - origin;

		int2 framebufferCoord;
		int2 bitmapCoord = bitmapRelativeRectMin;
		for (framebufferCoord.y = rectMin.y; framebufferCoord.y < rectMax.y; framebufferCoord.y++, bitmapCoord.y++) {
			color8* framebufferRow = framebuffer->data + (framebuffer->size.x * framebufferCoord.y);
			uint8* bitmapRow = bitmap->data + (bitmap->size.x * bitmapCoord.y);

			bitmapCoord.x = bitmapRelativeRectMin.x;
			for (framebufferCoord.x = rectMin.x; framebufferCoord.x < rectMax.x; framebufferCoord.x++, bitmapCoord.x++) {
				color8 dstColor = framebufferRow[framebufferCoord.x];

				uint8 bitmapAlpha = bitmapRow[bitmapCoord.x];
				color8 srcColor = {
					bitmapAlpha * color.r / 255,
					bitmapAlpha * color.g / 255,
					bitmapAlpha * color.b / 255
				};

				color8 blendedColor = blendColors(dstColor, srcColor, bitmapAlpha);

				framebufferRow[framebufferCoord.x] = blendedColor;
			}
		}
	}

	void drawText(
		const char* text,
		const Font* const font,
		color8alpha color,
		int2 origin,
		const Framebuffer* const framebuffer
	) {
		int2 currentPos = origin;
		
		for(int i = 0; text[i] != '\0'; i++) {
			char c = text[i];

			const Font::GlyphInfo& glyphInfo = font->glyphInfo[c];

			drawBitmap(
				&font->glyphBitmaps[c],
				color,
				currentPos + glyphInfo.bearing,
				framebuffer
			);

			currentPos.x += glyphInfo.advance;
		}
	}
}