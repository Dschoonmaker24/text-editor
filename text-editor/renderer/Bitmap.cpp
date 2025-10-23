#include "Bitmap.hpp"

namespace Renderer {
	Bitmap::Bitmap(int2 size) {
		size.x = size.x < 1 ? 1 : size.x;
		size.y = size.y < 1 ? 1 : size.y;

		this->size = size;

		int pixelCount = size.x * size.y;
		this->data = new color8alpha[pixelCount];
	}

	Bitmap::~Bitmap() {
		delete[] data; 
	}
}