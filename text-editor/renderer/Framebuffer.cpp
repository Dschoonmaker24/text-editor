#include "Framebuffer.hpp"

#include <SDL3/SDL.h>

namespace Renderer {
    //only takes positive integers
    //framebuffer have a minimum size of 1x1, so this is fine
    int divideAndRoundUp(int value, int divisor) {
        return (value - 1) / divisor + 1;
    }
    
    //framebuffer size, with a minimum size of 1x1
    int2 getFramebufferSize(int2 desiredSize) {
        int2 size = desiredSize;
        size.x = size.x < 1 ? 1 : size.x;
        size.y = size.y < 1 ? 1 : size.y;
        
        return size;
    }

    int2 getDirectionalTileCount(int2 sizePixels) {
        int2 directionalTileCount;
        directionalTileCount.x = divideAndRoundUp(sizePixels.x, Framebuffer::TileSize);
        directionalTileCount.y = divideAndRoundUp(sizePixels.y, Framebuffer::TileSize);

        return directionalTileCount;
    }

    Framebuffer::Tile* initializeFramebufferTiles(int2 directionalTileCount) {
        int tileCount = directionalTileCount.x * directionalTileCount.y;

        return new Framebuffer::Tile[tileCount];
    }

    Framebuffer::Framebuffer(int2 size) :
        size(
            getFramebufferSize(size)
        ),

        directionalTileCount(
            getDirectionalTileCount(
                getFramebufferSize(size)
            )
        ),
        
        tiles(
            initializeFramebufferTiles(
                getDirectionalTileCount(
                    getFramebufferSize(size)
                )
            )
        )
    {
        //nothing to do in constructor body -
        //everything is done in initializers
        
        //this has the benefit of working with const members,
        //but at the cost of readability and redundant computations
        //is it really worth it?
    }

    Framebuffer::~Framebuffer() {
        delete[] tiles;
    }

    void clearFramebuffer(Framebuffer* const framebuffer, color8 clearColor) {
        const int tileCount = framebuffer->directionalTileCount.x * framebuffer->directionalTileCount.y;

        for (int tileIndex = 0; tileIndex < tileCount; tileIndex++) {
            color8* const tileData = framebuffer->tiles[tileIndex].data;

            for (int i = 0; i < Framebuffer::TileSize2; i++) {
                color8* const pixel = tileData + i;

                *pixel = clearColor;
            }
        }
    }

    //only works on SDL_PIXELFORMAT_XRGB8888 format for now
    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    ) {
        SDL_LockSurface(surface);
        
        uint8* const pixels = (uint8*)surface->pixels;

        int2 globalPixelCoord;
        for (globalPixelCoord.y = 0; globalPixelCoord.y < surface->h; globalPixelCoord.y++) {
            uint8* const rowStart = (uint8*)(pixels + (surface->pitch * globalPixelCoord.y));
            for (globalPixelCoord.x = 0; globalPixelCoord.x < surface->w; globalPixelCoord.x += Framebuffer::TileSize) {
                int2 tileCoord = globalPixelCoord / int2(Framebuffer::TileSize, Framebuffer::TileSize);

                Framebuffer::Tile& tile = framebuffer->tiles[tileCoord.x + framebuffer->directionalTileCount.x * tileCoord.y];
                const color8* const framebufferSection = tile.data + Framebuffer::TileSize * (globalPixelCoord.y % Framebuffer::TileSize);

                for (int i = 0; i < Framebuffer::TileSize; i++) {
                    const color8 framebufferPixel = framebufferSection[i];

                    //SDL's surface pixels are 4 bytes each
                    //use multiples of 4 bytes to find the correct pixel,
                    //then just set unused alpha to 255
                    uint8* const surfacePixel = rowStart + (4 * (globalPixelCoord.x+i));
                    
                    surfacePixel[0] = framebufferPixel.b;
                    surfacePixel[1] = framebufferPixel.g;
                    surfacePixel[2] = framebufferPixel.r;
                    surfacePixel[3] = 255;
                }
            }
        }

        SDL_UnlockSurface(surface);
    }
}