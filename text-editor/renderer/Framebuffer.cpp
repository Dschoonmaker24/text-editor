#include "Framebuffer.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
	Framebuffer::Framebuffer(int2 size) {
		size.x = size.x < 1 ? 1 : size.x;
		size.y = size.y < 1 ? 1 : size.y;

		this->size = size;

		int pixelCount = size.x * size.y;

		this->data = new color8[pixelCount];
	}

	Framebuffer::~Framebuffer() {
		delete[] data;
	}

	void clearFramebuffer(Framebuffer* const framebuffer, color8 clearColor) {
		const int pixelCount = framebuffer->size.x * framebuffer->size.y;

		for (int i = 0; i < pixelCount; i++) {
			color8& pixel = framebuffer->data[i];

			pixel = clearColor;
		}
	}

	//only works on SDL_PIXELFORMAT_XRGB8888 format for now
	//framebuffer and surface must be the same size
	void copyFramebufferToSurface(
		const Framebuffer* const framebuffer,
		SDL_Surface* const surface
	) {
		SDL_LockSurface(surface);
		
		uint8* const surfacePixels = (uint8*)surface->pixels;

		int2 pixelCoord;
		for (pixelCoord.y = 0; pixelCoord.y < surface->h; pixelCoord.y++) {
			uint8* const surfaceRow =
				(uint8*)(surfacePixels + (surface->pitch * pixelCoord.y));
			
			const color8* const framebufferRow =
				framebuffer->data + (framebuffer->size.x * pixelCoord.y);

			for (pixelCoord.x = 0; pixelCoord.x < surface->w; pixelCoord.x++) {
				const color8 framebufferPixel = framebufferRow[pixelCoord.x];
				
				//SDL's surface pixels are 4 bytes each
				//use a stride of 4 bytes to find the correct pixel,
				//and set the unused alpha to 255
				uint8* const surfacePixel = surfaceRow + (4 * pixelCoord.x);
					
				surfacePixel[0] = framebufferPixel.b;
				surfacePixel[1] = framebufferPixel.g;
				surfacePixel[2] = framebufferPixel.r;
				surfacePixel[3] = 255;
			}
		}

		SDL_UnlockSurface(surface);
	}
}