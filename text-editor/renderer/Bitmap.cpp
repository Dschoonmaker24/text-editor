#include "Bitmap.hpp"

#include <string.h>

namespace Renderer {
	Bitmap::Bitmap(int2 size) {
		size.x = size.x < 1 ? 1 : size.x;
		size.y = size.y < 1 ? 1 : size.y;

		this->size = size;

		int pixelCount = size.x * size.y;
		this->data = new uint8[pixelCount];
	}

	Bitmap::Bitmap(const Bitmap& bitmap) {
		size = bitmap.size;

		int pixelCount = size.x * size.y;
		data = new uint8[pixelCount];

		memcpy(data, bitmap.data, pixelCount * sizeof(data[0]));
	}

	Bitmap& Bitmap::operator=(const Bitmap & bitmap) {
		size = bitmap.size;

		int pixelCount = size.x * size.y;
		data = new uint8[pixelCount];

		memcpy(data, bitmap.data, pixelCount * sizeof(data[0]));

		return *this;
	}

	Bitmap::~Bitmap() {
		if (data != nullptr) {
			delete[] data;
		}
	}

	void Bitmap::resize(int2 newSize) {
		if (data != nullptr) {
			delete[] data;
		}

		size = newSize;

		int pixelCount = size.x * size.y;
		this->data = new uint8[pixelCount];
	}
}