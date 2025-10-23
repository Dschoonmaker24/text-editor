#pragma once

namespace Renderer {
	struct Bitmap {
		const int2 size;

		color8alpha* const data;

		Bitmap(int2 size);
		~Bitmap();
	};
}