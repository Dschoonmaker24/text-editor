#include "FontLoader.hpp"

#include <freetype/freetype.h>

#include <stdio.h>

namespace FontLoader {
	FT_Library FtLibrary;
	
	FontData::FontData() {
		ftFace = nullptr;
	}
	FontData::~FontData() {
		if (ftFace != nullptr) {
			FT_Done_Face(ftFace);
		}
	}

	void initialize() {
		FT_Init_FreeType(&FtLibrary);
	}

	void shutdown() {
		FT_Done_FreeType(FtLibrary);
	}

	void loadFontDataFromFile(const char* file, FontData* fontData) {
		FT_New_Face(FtLibrary, "arial.ttf", 0, &fontData->ftFace);
	}

	void generateFontFromFontData(FontData* fontData, int pixelSize, Renderer::Font& font) {
		Renderer::Bitmap errorBitmap({ 1, 1 });
		errorBitmap.data[0] = 255;

		FT_Set_Pixel_Sizes(fontData->ftFace, 0, pixelSize);

		for (unsigned int glyphIndex = 0; glyphIndex < 256; glyphIndex++) {
			Renderer::Font::GlyphInfo& glyphInfo = font.glyphInfo[glyphIndex];
			Renderer::Bitmap& bitmap = font.glyphBitmaps[glyphIndex];

			FT_Error error = FT_Load_Char(fontData->ftFace, glyphIndex, FT_LOAD_RENDER);

			if (error != FT_Err_Ok) {
				bitmap = errorBitmap;
				
				continue;
			}

			FT_GlyphSlot ftGlyph = fontData->ftFace->glyph;

			glyphInfo.bearing = int2 {
				ftGlyph->bitmap_left,
				-ftGlyph->bitmap_top
			};

			//convert from fixed-point fraction to integer number of pixels
			glyphInfo.advance = ftGlyph->advance.x >> 6;

			bitmap.resize(int2 {
				(int)ftGlyph->bitmap.width,
				(int)ftGlyph->bitmap.rows
			});

			int2 coord;
			for (coord.y = 0; coord.y < bitmap.size.y; coord.y++) {
				const unsigned char* const srcRow = ftGlyph->bitmap.buffer + (ftGlyph->bitmap.pitch * coord.y);
				uint8* const dstRow = bitmap.data + (bitmap.size.x * coord.y);

				for (coord.x = 0; coord.x < bitmap.size.x; coord.x++) {
					const unsigned int alpha = srcRow[coord.x];

					dstRow[coord.x] = alpha;
				}
			}
		}
	}
}