#pragma once

namespace Renderer {
	//single channel bitmap
	struct Bitmap {
		//size of the bitmap, read-only
		int2 size;

		uint8* data;

		Bitmap() {
			size = int2{0, 0};
			data = nullptr;
		}
		Bitmap(int2 size);
		Bitmap(const Bitmap& bitmap);
		Bitmap& operator=(const Bitmap& bitmap);

		~Bitmap();

		void resize(int2 newSize);
	};
}