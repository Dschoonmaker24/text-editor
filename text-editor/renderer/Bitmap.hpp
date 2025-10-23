#pragma once

namespace Renderer {
	struct Bitmap {
		int2 size;

		color8alpha* data;

		Bitmap(int2 size);
		~Bitmap();
	};
}