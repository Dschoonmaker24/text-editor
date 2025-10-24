#pragma once

#include "Bitmap.hpp"

namespace Renderer {
	struct Font {
		struct GlyphInfo {
			//offset of glyph relative to the origin, in pixels
			int2 bearing;
			//offset to next glyph, in pixels
			int advance;
		};

		//array of glyph info
		GlyphInfo* glyphInfo;
		//array of glyph bitmaps
		Bitmap* glyphBitmaps;
		
		Font() {
			glyphInfo = new GlyphInfo[256];
			glyphBitmaps = new Bitmap[256];
		}
		Font(const Font& font) = delete;
		Font& operator=(const Font& font) = delete;

		~Font() {
			delete[] glyphInfo;
			delete[] glyphBitmaps;
		}
	};
}