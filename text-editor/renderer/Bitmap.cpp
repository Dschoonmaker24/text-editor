#include "Bitmap.hpp"

namespace Renderer {
	//returns bitmap size, with a minimum size of 1x1
	int2 bitmapSize(int2 desiredSize) {
		int2 size = desiredSize;
		size.x = size.x < 1 ? 1 : size.x;
		size.y = size.y < 1 ? 1 : size.y;

		return size;
	}

	color8alpha* allocateBitmapData(int2 size) {
		int pixelCount = size.x * size.y;

		return new color8alpha[pixelCount];
	}

	Bitmap::Bitmap(int2 size) :
		size(bitmapSize(size)),
		data(allocateBitmapData(bitmapSize(size)))
	{
		
	}

	Bitmap::~Bitmap() {
		delete[] data;
	}
}