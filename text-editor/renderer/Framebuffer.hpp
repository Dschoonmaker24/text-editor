#pragma once

struct SDL_Surface;

namespace Renderer {
    struct Framebuffer {
        //size of a square framebuffer tile
        constexpr static int TileSize = 32;
        //tile size squared
        constexpr static int TileSize2 = TileSize * TileSize;

        struct Tile {
            unsigned char data[3 * TileSize2];
        };

        const int width, height;
        const int tileCountX, tileCountY;

        Tile* const tiles;

        Framebuffer(int width, int height);
        ~Framebuffer();
    };

    void clearFramebuffer(Framebuffer* const framebuffer, unsigned char clearValue[3]);

    void copyFramebufferToSurface(
        const Framebuffer* const framebuffer,
        SDL_Surface* const surface
    );
}