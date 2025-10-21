#include "Framebuffer.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
    //only takes positive integers
    //framebuffer have a minimum size of 1x1, so this is fine
    int divideAndRoundUp(int value, int divisor) {
        return (value - 1) / divisor + 1;
    }

    //set reasonable limits on framebuffer size,
    //e.g. only positive sizes
    int clampFramebufferDimension(int framebufferDimension) {
        return framebufferDimension < 1 ? 1 : framebufferDimension;
    }

    Framebuffer::Tile* initializeFramebufferTiles(int pixelWidth, unsigned int pixelHeight) {
        int tileCountX = divideAndRoundUp(pixelWidth, Framebuffer::TileSize);
        int tileCountY = divideAndRoundUp(pixelHeight, Framebuffer::TileSize);

        int tileCount = tileCountX * tileCountY;

        return new Framebuffer::Tile[tileCount];
    }

    //doing redundant computations in initializers
    //is this really worth it to make the framebuffer immutable?
    Framebuffer::Framebuffer(int width, int height) :
        width(clampFramebufferDimension(width)),
        height(clampFramebufferDimension(height)),

        tileCountX(divideAndRoundUp(clampFramebufferDimension(width), Framebuffer::TileSize)),
        tileCountY(divideAndRoundUp(clampFramebufferDimension(height), Framebuffer::TileSize)),

        tiles(initializeFramebufferTiles(
            clampFramebufferDimension(width),
            clampFramebufferDimension(height)
        ))
    {
    }

    Framebuffer::~Framebuffer() {
        delete[] tiles;
    }

    void clearFramebuffer(Framebuffer* const framebuffer, unsigned char clearValue[3]) {
        const int tileCount = framebuffer->tileCountX * framebuffer->tileCountY;

        for (int tileIndex = 0; tileIndex < tileCount; tileIndex++) {
            unsigned char* const tileData = framebuffer->tiles[tileIndex].data;

            for (int i = 0; i < Framebuffer::TileSize2; i++) {
                unsigned char* const pixel = tileData + (3 * i);

                pixel[0] = clearValue[0];
                pixel[1] = clearValue[1];
                pixel[2] = clearValue[2];
            }
        }
    }

    //only works on SDL_PIXELFORMAT_XRGB8888 format for now
    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    ) {
        SDL_LockSurface(surface);
        
        unsigned char* const pixels = (unsigned char*)surface->pixels;

        for (int y = 0; y < surface->h; y++) {
            unsigned char* const rowStart = (unsigned char*)(pixels + (surface->pitch * y));
            for (int x = 0; x < surface->w; x += Framebuffer::TileSize) {
                int tileCoordX = x / Framebuffer::TileSize;
                int tileCoordY = y / Framebuffer::TileSize;

                Framebuffer::Tile& tile = framebuffer->tiles[tileCoordX + framebuffer->tileCountX * tileCoordY];
                unsigned char* const framebufferSection = tile.data + 3*(Framebuffer::TileSize * (y % Framebuffer::TileSize));

                for (int i = 0; i < Framebuffer::TileSize; i++) {
                    const unsigned char* const framebufferPixel = framebufferSection + (3 * i);

                    unsigned char* const surfacePixel = rowStart + (4 * (x+i));

                    surfacePixel[0] = framebufferPixel[2];
                    surfacePixel[1] = framebufferPixel[1];
                    surfacePixel[2] = framebufferPixel[0];
                    surfacePixel[3] = 255;
                }
            }
        }

        SDL_UnlockSurface(surface);
    }
}