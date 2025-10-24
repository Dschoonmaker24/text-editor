#pragma once

#include "Renderer/Font.hpp"

struct FT_FaceRec_;
typedef struct FT_FaceRec_* FT_Face;

namespace FontLoader {
	//intermediate data used to generate font bitmaps
	//it is useful to keep this after loading it from a file,
	//so that bitmaps can be generated at different sizes when needed
	struct FontData {
		FT_Face ftFace;

		FontData();
		~FontData();
	};

	void initialize();
	void shutdown();

	void loadFontDataFromFile(const char* file, FontData* fontData);
	void generateFontFromFontData(FontData* fontData, int pixelSize, Renderer::Font& font);
}